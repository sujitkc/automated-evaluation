#!/usr/bin/python3

import sys
import os
import csv
import string
import subprocess
import functools

class QType:
  def __init__(self, n, tm):
    self.domainSize = n
    self.totalMarks = float(tm)

class MCQType(QType):
  def __init__(self, n, tm):
    QType.__init__(self, n, tm)

class MTFQType(QType):
  def __init__(self, n1, n2, tm):
    QType.__init__(self, n1, tm)
    self.rangeSize = n2

# Read from file the model answers and prepare a list of questions.
# qtypes: Question type list. qtypes[i] is the question type of
# i-th line in the input file. 
# Reading rules:
# - When reading i-th line from the file, refer to qtypes[i]
# - If qtype[i] = MCQ(n), expect each cell to contain an integer.
# - Else If qtype[i] = MTF(n1, n2)
#     * expect each cell to contain a list of integers.
#     * expect there to be exactly n1 number of cells in the row.
#     * Each integer in a cell should be in the range (1, n2).
#     * A cell may sometime be a list [0], in which case we assume that the
#         corresponding option has not been attempted.
# - Else (if qtype[i] = None)
#     This line should be ignored

class QuestionPaper:
  def __init__(self, questions, qtypes):
    self.questions = questions
    self.questionTypes = qtypes

  def evaluate(self, answers, rollNumber="reference"):

    itemScores = []
    for i in range(len(self.questionTypes)):
      itemScore = 0.0
      try:
        question = self.questions[i]
        answer = answers.answers[i]
        if(question != None):
          itemScore = question.evaluate(answer)
        else:
          itemScore = 0
      except IncompatibleLengthError:
        print("Could not evaluate item " + str(i + 1) + " for " + rollNumber)
        raise
      itemScores.append(itemScore)

    return Score(rollNumber, itemScores)

  def __str__(self):
    return "Question Paper(" + str([str(q) for q in self.questions]) + ")"

class AnswerSheet:
  def __init__(self, answers):
    self.answers = answers

  def __str__(self):
    return "Answer Sheet(" + str([str(a) for a in self.answers]) + ")"

class Reader:
  def __init__(self, qtypes):
    self.questionTypes = qtypes

  def __readContents__(self, fileName):
    if(not os.path.isfile(fileName)):
      print(fileName + ": file does not exist.")
      raise FileNotExistsError(fileName)
    ifile  = open(fileName, "r")
    csvContents = csv.reader(ifile)
    trimmedContents = []
    rowNum = 0
    # for row in csvContents:
    rows = list(csvContents)
    while(rowNum < len(self.questionTypes)):
      row = rows[rowNum]
      trimmedRow = [cell for cell in row if cell is not ""]
      if(len(trimmedRow) != 0):
        trimmedContents.append(self.parseRow(trimmedRow, rowNum))
      else:
        trimmedContents.append(None)
      rowNum += 1
    return trimmedContents

  def parseRow(self, row, i):
    qtype = self.questionTypes[i]
    if(type(qtype) == MCQType):
      return self.parseMCQ(row, qtype)
    elif(type(qtype) == MTFQType):
      return self.parseMTF(row, qtype)
    else:
      return None

  @staticmethod
  def parseMTFRow(row):
    def getChoices(ans):
      splitAns = ans.split(",")
      return [int(s.strip()) for s in splitAns]

    return [getChoices(cell) for cell in row]

# ReferenceReader assumes that it is reading a reference file. Hence,
#  it'll generate a list of questions.
class ReferenceReader(Reader):
  def __init__(self, qtypes):
    Reader.__init__(self, qtypes)

  @staticmethod
  def parseMCQ(row, qtype):
    return MCQuestion([int(cell) for cell in row], qtype)

  @staticmethod
  def parseMTF(row, qtype):
    mtfrow = Reader.parseMTFRow(row)
    mcqs = [ReferenceReader.parseMCQ(cell, MCQType(qtype.rangeSize, 1.0/qtype.rangeSize)) for cell in mtfrow]
    return MTFQuestion(mcqs, qtype)

  def readQuestionPaper(self, fileName):
    return QuestionPaper(self.__readContents__(fileName), self.questionTypes)
 
# AnswerReader assumes that it is reading an answer file. Hence, it'll
#  generate a list of answers.
class AnswerReader(Reader):
  def __init__(self, qtypes):
    Reader.__init__(self, qtypes)

  @staticmethod
  def parseMCQ(row, qtype):
    return [int(cell) for cell in row]

  @staticmethod
  def parseMTF(row, qtype):
    return Reader.parseMTFRow(row)

  def readAnswers(self, fileName):
    return AnswerSheet(self.__readContents__(fileName))

# Exception class to deal with the situation when the submission doesn't match in length
# with the expected. It may happen when:
# - when the number of items in the output is different from that in the expected.
# - when the number of choices in the individual item is different.
# - ... or in other unforeseen situations of similar type.
class IncompatibleLengthError(Exception):
  def __init__(self, e, a):
    self.expected = e
    self.answer   = a

  def __str__(self):
    return "IncompatibleLengthError(expected = " + str(self.expected) + ", answer = " + str(self.answer) + ")"

class FileNotExistsError(Exception):
  def __init__(self, filename):
    Exception.__init__(self, "File " + filename + " doesn't exist.")

class Question:
  def __init__(self, e, qtype):
    self.expected = e
    self.questionType = qtype
    
  @property
  def domainSize(self):
    return self.questionType.domainSize

class MCQuestion(Question):
  def __init__(self, e, qtype):
    Question.__init__(self, e, qtype)
    self.expectedChoices = self.convert(self.expected)

  def convert(self, indices):
    choices = [False] * self.domainSize
    for i in indices:
      choices[int(i) - 1] = True # the - 1 is to deal with the offset of index.
    return choices

  # Given an expected answer and output answer, compare choice by choice.
  # The score is out of 1. It is the fraction of choices that match to the total number of
  # choices.
  def score(self, answer):
    if(len(self.expectedChoices) != len(answer)):
      raise IncompatibleLengthError(len(self.expectedChoices), len(answer))
    score = 0
    zipped = zip(self.expectedChoices, answer)
    for (a, b) in zipped:
      if(a == b):
        score += 1
    return float(score) / float(self.domainSize)

  def evaluate(self, answer):
    expectedChoices = self.convert(self.expected)

    answerChoices = self.convert(answer)

    if(0 not in answer):
      return self.score(answerChoices) * self.questionType.totalMarks
    else:
      return 0

  def __str__(self):
    return "MCQ(" + str(self.domainSize) + ", " + str(self.expected) + ")"

class MTFQuestion(Question):
  def __init__(self, e, qtype):
    Question.__init__(self, e, qtype)

  @property
  def rangeSize(self):
    return self.questionType.rangeSize

  def evaluate(self, answer):
    def getChoices(ans):
      splitAns = ans.split(",")
      return [int(s.strip()) for s in splitAns]

    if(len(self.expected) != self.domainSize):
      raise IncompatibleLengthError(len(self.expected), len(answer))
    if(len(answer) != self.domainSize):
      raise IncompatibleLengthError(len(self.expected), len(answer))

    zipped = zip(self.expected, answer)
    return sum([q.evaluate(a) for (q, a) in zipped]) * self.questionType.totalMarks
    
  def __str__(self):
    return "MTF(" + str([str(q) for q in self.expected]) + \
      ", " + str(self.domainSize) + ", " + str(self.rangeSize) + ")"

# Class representing the score of an individual student.
class Score:
  def __init__(self, rollNumber, scores):
    self.rollNumber = rollNumber
    self.itemScores = scores

  @property
  def total(self):
    return functools.reduce(lambda x, y: x + y, self.itemScores, 0.0)

  def __str__(self):
    s = "roll number: " + self.rollNumber + "\n"
    s += "item scores: " + str(self.itemScores) + "\n"
    s += "total score: " + str(self.total) + "\n"
    return s

class Evaluator:
  def __init__(self):
    self.qreader = ReferenceReader(self.qtypes)
    self.areader = AnswerReader(self.qtypes)
    self.questionPaper = self.qreader.readQuestionPaper("theory-answers.csv")
    reference = self.areader.readAnswers("theory-answers.csv")
    self.referenceScore = self.questionPaper.evaluate(reference)

  @property
  def totalMarks(self):
    return self.referenceScore.total

  def __evaluate__(self, rollNumber):
    print("evaluating ", rollNumber, " ...")
    try:
      ansfile = "../submissions/theory/" + rollNumber + ".csv"
      answerSheet = self.areader.readAnswers(ansfile)
      return self.questionPaper.evaluate(answerSheet, rollNumber)
    except FileNotExistsError:
      return "File " + ansfile + " not found."
    except IncompatibleLengthError as e:
      return e
    except Exception as e:
      return e

  def evaluate(self):
    results = {}
    for rollNumber in self.rollNumbers:
      results[rollNumber] = self.__evaluate__(rollNumber)
    return results
