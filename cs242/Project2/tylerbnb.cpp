#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main () {

  const int dictionarySize = 8;
  const int documentTotal = 11;

  int classArray[documentTotal] = {0};

  double S = 0;
  double I = 0;
  double probS = 0;
  double probI = 0;
  double totalS = 1.0;
  double totalI = 1.0;
  double probWordS[dictionarySize] = {0};
  double probWordI[dictionarySize] = {0};
  int SwordsCount[dictionarySize] = {0};
  int IwordsCount[dictionarySize] = {0};
  char data;
  int documentCount = 0;
  string line;
  ifstream fin;

  /*****************************************************/

  fin.open("toy.class.txt", ios::in | ios::binary);
  if (fin.is_open()){
    int i = 0;
    while(fin >> data) {
      if(data == '1') {
	classArray[i] = 1;
	i++;
	S++;
      }
      else if(data == '0'){
	i++;
	I++;
      }
    }
  }
  else {
    cout << "Error: cannot open input file. \n";
  }
  fin.close();

  for (int i =0; i < 11; i++) {
    cout << classArray[i];
  }

  cout << endl;
  documentCount = (S+I);

  cout << S << endl;
  cout << I << endl;
  cout << documentCount << endl;

  probS = S/documentCount;
  probI = I/documentCount;

  cout << probS << endl;
  cout << probI << endl;

  /*******************************************************/

  fin.open("toy.data.txt", ios::in | ios::binary);
  if (fin.is_open()) {
    for( int j = 0; j < documentCount; j++) {
      for( int i =0 ; i < dictionarySize; i++) {
	fin >> data;
	if(classArray[j] == 1 && data == '1'){
	  SwordsCount[i] += 1;
	}
	else if(classArray[j] == 0 && data == '1') {
	  IwordsCount[i] += 1;
	}
      }
    }
  }
  else {
    cout << "Error: cannot open input file. \n";
  }
  fin.close();





  for (int i =0; i < dictionarySize; i++) {
    cout << SwordsCount[i] << " ";
  }
  cout << endl;
  for (int i =0; i < dictionarySize; i++) {
    cout << IwordsCount[i] << " ";
  }


  for (int i=0; i < dictionarySize; i++) {
    probWordS[i] = SwordsCount[i] / S;
    probWordI[i] = IwordsCount[i] / I;
  }

  fin.open("toytest.data.txt", ios::in | ios::binary);
  if (fin.is_open()) {
    for( int j = 0; j < 2; j++) {
      for (int i=0; i < dictionarySize; i++) {
	fin >> data;
	if(data == '1') {
	  totalS *= probWordS[i];
	  totalI *= probWordI[i];
	}
	else if(data == '0') {
	  totalS *= (1-probWordS[i]);
	  totalI *= (1-probWordI[i]);
	}
      }

      probS *= totalS;
      probI *= totalI;
      cout << "Test Case " << j + 1 << endl;
      cout << "\tP(S|b) = " << probS << endl;
      cout << "\tP(I|b) = " << probI << endl;
      probS /= totalS;
      probI /= totalI;
      totalS = 1.0;
      totalI = 1.0;
    }
  }
  else {
    cout << "Error: cannot open input file. \n";
  }
  fin.close();

  return 0;
}

