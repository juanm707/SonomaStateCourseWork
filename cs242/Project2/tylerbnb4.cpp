#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main () {

  /*****************************************************/
  // Variable declarations

  const int dictionarySize = 48;
  const int documentTotal = 4601;

  int spamHamArray[documentTotal] = {0};

  double actualSpam = 0;
  double trainingSpam = 0;
  double trainingHam = 0;
  double probSpam = 0;
  double probHam = 0;
  double testProbSpam = 1.0;
  double testProbHam = 1.0;
  double probWordSpam[dictionarySize] = {0};
  double probWordHam[dictionarySize] = {0};
  double accuracy;

  int predictionSpamTotal = 0;
  int wordCountSpam[dictionarySize] = {0};
  int wordCountHam[dictionarySize] = {0};
  int trainingCount = 0;
  int testCount = 0;

  char data;
  string line;
  string trainingDataFile;
  string trainingClassFile;
  string testDataFile;
  string testClassFile;
  ifstream fin;

  /*****************************************************/
  // Prompt the user for the file names

  cout << "Enter the names of training data, training class, test data, and test class files (in that order): " << endl;
  cin >> trainingDataFile >> trainingClassFile >> testDataFile >> testClassFile;

  /*****************************************************/
  // Read the training class from the text files.

  fin.open(trainingClassFile, ios::in);

  if (fin.is_open()){
    int i = 0;
    while(fin >> data) {
      if(data == '1') {
	spamHamArray[i] = 1;
	trainingSpam++;
	i++;
      }
      else if(data == '0'){
	trainingHam++;
	i++;
      }
    }
  }
  else {
    cout << "Error: cannot open input file. \n";
  }
  fin.close();

  trainingCount = (trainingSpam + trainingHam);
  testCount = documentTotal - trainingCount;

  // Calculate the prior probabilities for each class.

  probSpam = trainingSpam/trainingCount;
  probHam = trainingHam/trainingCount;

  // Read the data from data training file.

  fin.open(trainingDataFile, ios::in | ios::binary);
  if (fin.is_open()) {
    for( int j = 0; j < trainingCount; j++) {
      for (int i=0; i < dictionarySize; i++) {
	fin >> data;
	if(spamHamArray[j] == 1 && data == '1') {
	  wordCountSpam[i] += 1;
	}
	else if (spamHamArray[j] == 0 && data == '1') {
	  wordCountHam[i] += 1;
	}
      }
    }
  }
  else {
    cout << "Error: cannot open input file. \n";
  }
  fin.close();


  // Calculate the probabilities of each word.

  for (int i=0; i < dictionarySize; i++) {
    probWordSpam[i] = wordCountSpam[i] / trainingSpam;
    probWordHam[i] = wordCountHam[i] / trainingHam;
  }


  // Read data from the test file

  fin.open(testDataFile, ios::in | ios::binary);
  if (fin.is_open()) {
    for( int j = 0; j < testCount; j++) {
      testProbSpam = 1.0;
      testProbHam = 1.0;
      for (int i=0; i < dictionarySize; i++) {
	fin >> data;
	if(data == '1') {
	  testProbSpam *= probWordSpam[i];
	  testProbHam *= probWordHam[i];
	}
	else if(data == '0') {
	  testProbSpam *= (1-probWordSpam[i]);
	  testProbHam *= (1-probWordHam[i]);
	}
      }
      double isSpam = probSpam * testProbSpam;
      double isHam = probHam * testProbHam;

      if(isSpam > isHam) {
	predictionSpamTotal++;
      }

    }
  }
  else {
    cout << "Error: cannot open input file. \n";
  }
  fin.close();


  // Read the class test data from the text files.

  fin.open(testClassFile, ios::in | ios::binary);
  if (fin.is_open()){
    while(fin >> data) {
      if(data == '1') {
	actualSpam++;
      }
    }
  }
  else {
    cout << "Error: cannot open input file. \n";
  }
  fin.close();

  cout << actualSpam << endl;
  accuracy = predictionSpamTotal/actualSpam;

  cout << "Training using " << trainingCount << " cases" <<  endl;
  cout << "Evaluating " << testCount << " test cases" << endl;
  cout << "Successful detection rate of " << accuracy*100 << "%" << endl;

  return 0;
}

