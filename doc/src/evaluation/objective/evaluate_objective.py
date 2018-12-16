#!/usr/bin/python3

import sys
import os
import csv
import string
import subprocess
import functools

class QType:
  def __init__(self, n):
    self.domainSize = n

class MCQType(QType):
  def __init__(self, n):
    QType.__init__(self, n)

class MTFQType(QType):
  def __init__(self, n1, n2):
    QType.__init__(self, n1)
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
    for row in csvContents:
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
    return MCQuestion([int(cell) for cell in row], qtype.domainSize)

  @staticmethod
  def parseMTF(row, qtype):
    mtfrow = Reader.parseMTFRow(row)
    mcqs = [ReferenceReader.parseMCQ(cell, MCQType(qtype.rangeSize)) for cell in mtfrow]
    return MTFQuestion(mcqs, qtype.domainSize, qtype.rangeSize)

  def readQuestionPaper(self, fileName):
    return QuestionPaper(self.__readContents__(fileName), self.questionTypes)
 
# AnswerReader assumes that it is areading an answer file. Hence, it'll
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

class MCQuestion:
  def __init__(self, e, n):
    self.expected = e
    self.numberOfChoices = n
    self.expectedChoices = self.convert(self.expected)

  def convert(self, indices):
    choices = [False] * self.numberOfChoices
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
    return float(score) / float(self.numberOfChoices)

  def evaluate(self, answer):
    expectedChoices = self.convert(self.expected)

    answerChoices = self.convert(answer)

    if(0 not in answer):
      return self.score(answerChoices)
    else:
      return 0

  def __str__(self):
    return "MCQ(" + str(self.numberOfChoices) + ", " + str(self.expected) + ")"

class MTFQuestion:
  def __init__(self, e, d, r):
    self.expected   = e
    self.domainSize = d
    self.rangeSize  = r

  def evaluate(self, answer):
    def getChoices(ans):
      splitAns = ans.split(",")
      return [int(s.strip()) for s in splitAns]

    if(len(self.expected) != self.domainSize):
      raise IncompatibleLengthError(len(self.expected), len(answer))
    if(len(answer) != self.domainSize):
      raise IncompatibleLengthError(len(self.expected), len(answer))

    zipped = zip(self.expected, answer)
    return sum([q.evaluate(a) for (q, a) in zipped])
    
  def __str__(self):
    return "MTF(" + str([str(q) for q in self.expected]) + ", " + str(self.domainSize) + ", " + str(self.rangeSize) + ")"

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
  
# evaluate the answers submitted by the student rollNumber.
def evaluateRollNumber(rollNumber):
  print("roll number = ", rollNumber)
  expectedAnswers = readAnswers("theory-answers.csv")
  answers         = readAnswers("../submissions/theory/" + rollNumber + ".csv")
  return evaluate(expectedAnswers, answers, rollNumber=rollNumber)

def evaluateAll(studentList):
  scores = []
  for rollNumber in studentList:
    try:
      result = evaluateRollNumber(rollNumber)
      scores.append(result)
    except FileNotExistsError as e:
      print(e)
  return scores

imt2018 = [
  "imt2018066",
  "imt2018001",
  "imt2018002",
  "imt2018003",
  "imt2018004",
  "imt2018005",
  "imt2018501",
  "imt2018006",
  "imt2018007",
  "imt2018008",
  "imt2018009",
  "imt2018502",
  "imt2018503",
  "imt2018010",
  "imt2018011",
  "imt2018012",
  "imt2018504",
  "imt2018505",
  "imt2018013",
  "imt2018014",
  "imt2018015",
  "imt2018016",
  "imt2018017",
  "imt2018018",
  "imt2018019",
  "imt2018021",
  "imt2018022",
  "imt2018023",
  "imt2018024",
  "imt2018025",
  "imt2018026",
  "imt2018506",
  "imt2018027",
  "imt2018028",
  "imt2018029",
  "imt2018507",
  "imt2018508",
  "imt2018030",
  "imt2018031",
  "imt2018032",
  "imt2018033",
  "imt2018034",
  "imt2018035",
  "imt2018509",
  "imt2018510",
  "imt2018511",
  "imt2018036",
  "imt2018037",
  "imt2018512",
  "imt2018038",
  "imt2018513",
  "imt2018039",
  "imt2018040",
  "imt2018041",
  "imt2018514",
  "imt2018042",
  "imt2018043",
  "imt2018044",
  "imt2018045",
  "imt2018046",
  "imt2018047",
  "imt2018048",
  "imt2018049",
  "imt2018050",
  "imt2018051",
  "imt2018052",
  "imt2018053",
  "imt2018515",
  "imt2018516",
  "imt2018054",
  "imt2018055",
  "imt2018517",
  "imt2018056",
  "imt2018020",
  "imt2018057",
  "imt2018518",
  "imt2018058",
  "imt2018059",
  "imt2018519",
  "imt2018060",
  "imt2018520",
  "imt2018061",
  "imt2018062",
  "imt2018063",
  "imt2018064",
  "imt2018065",
  "imt2018067",
  "imt2018521",
  "imt2018068",
  "imt2018522",
  "imt2018069",
  "imt2018070",
  "imt2018523",
  "imt2018071",
  "imt2018072",
  "imt2018073",
  "imt2018074",
  "imt2018524",
  "imt2018075",
  "imt2018525",
  "imt2018526",
  "imt2018076",
  "imt2018077",
  "imt2018078",
  "imt2018527",
  "imt2018079",
  "imt2018080",
  "imt2018081",
  "imt2018082",
  "imt2018528",
  "imt2018529",
  "imt2018083",
  "imt2018084",
  "imt2018085",
  "imt2018086",
  "imt2018087",
  "imt2017029",
]

qtypes_et2018 = [
  MCQType(4),     #1
  MCQType(4),     #2
  MCQType(4),     #3
  MCQType(4),     #4
  MCQType(4),     #5
  MCQType(4),     #6
  MTFQType(4, 6), #7
  MCQType(4),     #8
  MCQType(4),     #9
  MTFQType(5, 5), #10
  MCQType(4),     #11
  MCQType(4),     #12
  MCQType(4),     #13
  MCQType(4),     #14
]

def eval_imt2018():

  allScores = evaluateAll(studentList)
  
  expectedAnswers = readAnswers("theory-answers.csv")
  answers         = readAnswers("theory-answers.csv")
  fullMarks = evaluate(expectedAnswers, answers)
  for studentScore in allScores:
    print(studentScore.rollNumber + " : " + str(studentScore.total) + " / " + str(fullMarks.total))

def t1():
  reader = AnswerReader(qtypes_et2018)
  print(reader.readAnswers("../submissions/theory/imt2018001.csv"))
 
def t2():
  reader = ReferenceReader(qtypes_et2018)
  print(reader.readQuestionPaper("theory-answers.csv"))

def t3():
  qreader = ReferenceReader(qtypes_et2018)
  areader = AnswerReader(qtypes_et2018)
 
  questionPaper = qreader.readQuestionPaper("theory-answers.csv")
  answerSheet = areader.readAnswers("../submissions/theory/imt2018001.csv")

  print(questionPaper.evaluate(answerSheet))

def t5():
  qreader = ReferenceReader(qtypes_et2018)
  areader = AnswerReader(qtypes_et2018)
 
  questionPaper = qreader.readQuestionPaper("theory-answers.csv")
  answerSheet = areader.readAnswers("theory-answers.csv")

  print(questionPaper.evaluate(answerSheet))


def t4():
  qreader = ReferenceReader(qtypes_et2018)
  areader = AnswerReader(qtypes_et2018)
 
  questionPaper = qreader.readQuestionPaper("theory-answers.csv")
  for rollNumber in imt2018:
    try:
      ansfile = "../submissions/theory/" + rollNumber + ".csv"
      answerSheet = areader.readAnswers(ansfile)
      print(questionPaper.evaluate(answerSheet, rollNumber))
    except FileNotExistsError:
      print("File " + ansfile + " not found.")
    except IncompatibleLengthError as e:
      print(rollNumber + " : " + str(e))

if __name__ == "__main__":
#  t1()
#  t2()
#  t3()
  t5()
  t4()
