#!/usr/bin/python3

import sys
import os
import csv
import string
import subprocess
import functools

MCQ = 0
MTF = 1
questionTypes = [
  (MCQ, 4), #1
  (MCQ, 4), #2
  (MCQ, 4), #3
  (MCQ, 4), #4
  (MCQ, 4), #5
  (MCQ, 4), #6
  (MTF, (4, 6)), #7
  (MCQ, 4), #8
  (MCQ, 4), #9
  (MTF, (5, 5)), #10
  (MCQ, 4), #11
  (MCQ, 4), #12
  (MCQ, 4), #13
  (MCQ, 4), #14
]

def questionType(q):
  return q[0]

def MTFdomSize(q):
  if(questionType(q) != MTF):
    raise EvaluationError("Incompatible question type.")
  return q[1][0]

def MTFrangeSize(q):
  if(questionType(q) != MTF):
    raise EvaluationError("Incompatible question type.")
  return q[1][1]

# Read the contents of the CSV file
def readAnswers(fileName):
  if(not os.path.isfile(fileName)):
    print(fileName + ": file does not exist.")
    raise FileNotExistsError(fileName)
  ifile  = open(fileName, "r")
  csvContents = csv.reader(ifile)
  trimmedContents = []
  for row in csvContents:
    trimmedRow = [cell for cell in row if cell is not ""]
    if(len(trimmedRow) != 0):
      trimmedContents.append(trimmedRow)
    else:
      trimmedContents.append(None)
  return trimmedContents

# Exception class to deal with the situation when the submission doesn't match in length
# with the expected. It may happen when:
# - when the number of items in the output is different from that in the expected.
# - when the number of choices in the individual item is different.
# - ... or in other unforeseen situations of similar type.
class IncompatibleLengthError(Exception):
  def __init__(self, e, o):
    self.expected = e
    self.output   = o

class FileNotExistsError(Exception):
  def __init__(self, filename):
    Exception.__init__(self, "File " + filename + " doesn't exist.")

# Given an expected answer and output answer, compare choice by choice.
# The score is out of 1. It is the fraction of choices that match to the total number of
# choices.
def score(expected, output):
  if(len(expected) != len(output)):
    raise IncompatibleLengthError(len(expected), len(output))
  score = 0
  zipped = zip(expected, output)
  for (a, b) in zipped:
    if(a == b):
      score += 1
  numOfChoices = len(expected)
  return float(score) / float(numOfChoices)

def evaluateMCQ(expected, output, numOfChoices):
  def convert(indices):
    choices = [False] * numOfChoices
    for i in indices:
      choices[int(i) - 1] = True # the - 1 is to deal with the offset of index.
    return choices

  if("0" in output): # indicates that the question has not been attempted.
    return 0
  expectedChoices = convert(expected)
  outputChoices   = convert(output)

  return score(expectedChoices, outputChoices)

def evaluateMTF(expected, output, domSize, rangeSize):
  def getChoices(ans):
    splitAns = ans.split(",")
    return [int(s.strip()) for s in splitAns]

  if(len(expected) != domSize):
    raise IncompatibleLengthError(len(expected), len(output))
  if(len(output) != domSize):
    raise IncompatibleLengthError(len(output), len(output))

  zipped = zip(expected, output)
  return sum([evaluateMCQ(getChoices(ch_exp), getChoices(ch_out), rangeSize) for (ch_exp, ch_out) in zipped])
    
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

def evaluate(expectedAnswers, answers, rollNumber="reference"):
  if(len(expectedAnswers) != len(questionTypes) or len(answers) != len(questionTypes)):
    print(str(rollNumber) + " : " + str(expectedAnswers) + ", " + str(answers))
    raise IncompatibleLengthError((len(expectedAnswers), len(answers)))

  itemScores = []
  for i in range(len(questionTypes)):
    itemScore = 0.0
    try:
      qtype = questionTypes[i]
      expected = expectedAnswers[i]
      answer = answers[i]
      if(answer == None):
        itemScore = 0
      elif(questionType(qtype) == MCQ):
        itemScore = evaluateMCQ(expected, answer, questionTypes[i][1])
      elif(questionType(qtype) == MTF):
        itemScore = evaluateMTF(expected, answer, MTFdomSize(qtype), MTFrangeSize(qtype))
    except(IncompatibleLengthError):
      print("Could not evaluate item " + str(i + 1) + " for " + rollNumber)
    itemScores.append(itemScore)

  return Score(rollNumber, itemScores)

def evaluateAll(studentList):
  scores = []
  for rollNumber in studentList:
    try:
      result = evaluateRollNumber(rollNumber)
      scores.append(result)
    except FileNotExistsError as e:
      print(e)
  return scores

if __name__ == "__main__":
  studentList = [
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
  allScores = evaluateAll(studentList)
  
  expectedAnswers = readAnswers("theory-answers.csv")
  answers         = readAnswers("theory-answers.csv")
  fullMarks = evaluate(expectedAnswers, answers)
  for studentScore in allScores:
    print(str(studentScore))

  print("full marks = ", fullMarks)
