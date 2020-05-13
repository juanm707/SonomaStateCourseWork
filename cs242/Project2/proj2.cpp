#include <iostream>
#include <fstream>
using namespace std;

float docCount(string filename, float & first, float & second);
//bool NCount_binary(string file, char SArray[][8], char IArray[][8], int sRows, int iRows);
	       
int main()
{
  // Document counter
  string file = "toy.class.txt";
  float S = 0;
  float I = 0;
  float totalDoc = docCount(file, S, I);
  
  //  cout << S << " sports documents " << I << " info documents " << totalDoc << " total documents" << endl;

  // Prob of each class
  float class_S = (S + 0.0)/totalDoc;
  float class_I = (I + 0.0)/totalDoc;

  // cout << "prob of sports doc " << class_S << " prob of info doc " << class_I << endl;
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  
  // N array (S or I sports documents, 8 words in dictionary
  const int dict = 8;
  
  char s_array [int(S)][dict];
  char i_array [int(I)][dict];
  
  ifstream ifile;
  ifile.open( "toy.data.txt");

  /////////////////////////////////////////////////////////////////////
  //Stores 1 and 0 in arrays

  for (int i = 0; i < int(S); i++)
    {
       for (int j = 0; j < dict; j++)
	{
	  ifile >> s_array[i][j];
	}
    }
  
  for (int i = 0; i < int(I); i++)
    {
      for (int j = 0; j < dict; j++)
	{
	  ifile >> i_array[i][j];
	}
    }

  ifile.close();
  ///////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////
  // W sub i
  int s_Wcount [dict] = { };
  int i_Wcount [dict] = { };
  
  for (int col = 0; col < dict; col++)
    {
     int w_counter = 0;

     for (int row  = 0; row < int(S); row++)
	{
	  if (s_array[row][col] == '1')
	    {
	      w_counter++;
	    }
	}

      s_Wcount[col] = w_counter;
    }

  for (int col = 0; col < dict; col++)
    {
      int w_counter = 0;
      for (int row = 0; row < int(I); row ++)
	{
	  if (i_array[row][col] == '1')
	    {
	      w_counter++;
	    }
	}
      i_Wcount[col] = w_counter;
    }
  //////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////
  // p(Wt | S)  
  float word_probS [dict] = { };

  for (int i = 0; i < dict; i++)
    {
      word_probS[i] = s_Wcount[i] / S;
      // cout << "SPORTS " <<  word_probS[i] << endl;
    }

  // p(Wt | I)
  float word_probI [dict] = { };

  for (int i = 0; i < dict; i++)
    {
      word_probI[i] = i_Wcount[i] / I;
      //cout << "INFO " << word_probI[i] << endl;
    }
  
  //////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////
  // P(C|D)
  ifstream I_file;
  I_file.open("toytest.data.txt");
  
  char f;
  float total_of_fS = 1.0;
  float total_of_fI = 1.0;

  // TEST CASE 1 //

  for (int i = 0; i < dict; i++)
    {
      I_file >> f;
      if (f == '1')
	{
	  total_of_fS *= word_probS[i];
	  total_of_fI *= word_probI[i];
	}
      else if (f == '0')
	{
	  total_of_fS *= (1 - word_probS[i]);
	  total_of_fI *= (1 - word_probI[i]);
	}
    }
  //////////////////////////////////////////////////////

  //OUTPUT//////////////////////////////////////////////
  // P(C = S|D)
  float isSport = class_S * total_of_fS;
 
  // P(C = I|D)
  float isInfo = class_I * total_of_fI;
  
  cout << "Test case 1"<< endl;
  cout << "\tp(S|b) = " << isSport << endl;
  cout << "\tp(I|b) = " << isInfo << endl;
  //////////////////////////////////////////////////////////

  // TEST CASE 2 //
  total_of_fS = 1.0;
  total_of_fI = 1.0;

  for (int i = 0; i < dict; i++)
    {
      I_file >> f;
      if (f == '1')
	{
	  total_of_fS *= word_probS[i];
	  total_of_fI *= word_probI[i];
	}
      else if (f == '0')
	{
	  total_of_fS *= (1 - word_probS[i]);
	  total_of_fI *= (1 - word_probI[i]);
	}
    }

  //OUTPUT//////////////////////////////////////////////
  // P(C = S|D)
  isSport = class_S * total_of_fS;

  // P(C = I|D)
  isInfo = class_I * total_of_fI;

  cout << "Test case 2"<< endl;
  cout << "\tp(S|b) = " << isSport << endl;
  cout << "\tp(I|b) = " << isInfo << endl;
  
  
  return 0;
}

//Implementation
float docCount(string filename, float & first, float & second)
{
  char c;
  float totalnumDoc = 0.0;

  //Open file for num of each docs
  ifstream in_file;
  in_file.open(filename.c_str());

  while (in_file >> c)
    {
      if (c == '1')
	{
	  first += 1.0;
	}
      else if (c == '0')
	{
	  second += 1.0;
	}
      
      totalnumDoc += 1.0;
    }

  in_file.close();
  
  return totalnumDoc;
}

/*
bool NCount_binary(string file, char SArray[][8], char IArray[][8], int sRows, int iRows)
{
  ifstream ifile;
  ifile.open(file.c_str());

  //Stores 1 and 0 in arrays

  for (int i = 0; i < sRows; i++)
    {
      for (int j = 0; j < 8; j++)
	{
	  ifile >> SArray[i][j];
	}
    }

  for (int i = 0; i < iRows; i++)
    {
      for (int j = 0; j < 8; j++)
	{
	  ifile >> IArray[i][j];
	}
    }
  
  ifile.close();
  
  return true;
  }*/
  
