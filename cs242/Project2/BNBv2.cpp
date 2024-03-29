#include <iostream>
#include <fstream>
using namespace std;

float docCount(string filename, float & first, float & second);
	       
int main()
{
  string data1;
  string class1;
  string data2;
  string class2;

  cout << "Enter the names of the training data, training class, test data and test class files (in that order): " << endl;
  cin >> data1 >> class1 >> data2 >> class2;
  
  // Document counter
  string file = class1;
  float S = 0;
  float I = 0;
  float totalDoc = docCount(file.c_str(), S, I);
  cout << "Training using " << totalDoc << " cases" << endl;
  // cout << "Evaluating " << S << ' ' << I << " test cases" << endl;
  // cout << S << " spam documents " << I << " ham documents " << totalDoc << " total documents" << endl;

  float ignore1 = 0;
  float ignore2 = 0;
  float evaluate = docCount(class2.c_str(), ignore1, ignore2);
  cout << "Evaluating " << evaluate << " test cases" << endl;

  
  // Prob of each class
  float class_S = (S + 0.0)/totalDoc;
  float class_I = (I + 0.0)/totalDoc;

  // cout << "prob of sports doc " << class_S << " prob of info doc " << class_I << endl;
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  
  // N array (S or I sports documents, 8 words in dictionary
  const int dict = 48;
  
  char s_array [int(S)][dict];
  char i_array [int(I)][dict];
  ifstream classfile;
  classfile.open(file.c_str());
   
  ifstream ifile;
  ifile.open(data1.c_str());

  /////////////////////////////////////////////////////////////////////
  //Stores 1 and 0 in arrays
  char check;
  char dataa;
  int w = 0;
  int i = 0;
  
  while (classfile >> check)
    {
      
      if (check == '1' && w < int(S))
	{
	  for (int j = 0; j < dict; j++)
	    {
    	      ifile >> dataa;
	      s_array[w][j] = dataa;
	    }
	  w++;
	}
      else if (check == '0' && i < int(I))
	{
	  for (int b = 0; b < dict; b++)
	    {
	      ifile >> dataa;
	      i_array[i][b] = dataa;
	    }
	  
	  i++;
	}
    }

  ifile.close();
  classfile.close();
  
  ///////////////////////////////////////////////////////////////////////
  /*  cout << "i_array is: " << endl << endl << endl;
  for ( int xx = 0; xx < int(I); xx++)
    {
      for (int yy = 0; yy < dict; yy++)
	{
	  cout << i_array[xx][yy];
	}
	cout << endl;}*/

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
      // cout << w_counter << ' ';
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
    }

  // p(Wt | I)
  float word_probI [dict] = { };

  for (int i = 0; i < dict; i++)
    {
      word_probI[i] = i_Wcount[i] / I;
    }
  
  //////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////
  // P(C|D)
  ifstream I_file;
  I_file.open(data2.c_str());

  ifstream testclass;
  testclass.open(class2.c_str());
  char checkclass;
  
  char f;
  float total_of_fS = 1.0;
  float total_of_fI = 1.0;

  float spam = 0;
  float ham = 0;
  // TEST CASE //
  for (int cases = 0; cases < evaluate; cases++)
    {
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
    
  //////////////////////////////////////////////////////

  //OUTPUT//////////////////////////////////////////////
  // P(C = S|D)
      float isSport = class_S * total_of_fS;
      
  // P(C = I|D)
      float isInfo = class_I * total_of_fI;
      //cout << "Test case " << cases + 1 << endl;
      //cout << "\tp(S|b) = " << isSport << endl;
      //cout << "\tp(I|b) = " << isInfo << endl;

      testclass >> checkclass;
      //cout << "Class value: " << checkclass << endl;
      
      if (isSport > isInfo)
	{ 
	  if (checkclass == '1')
	    {
	      //cout << "adding one to spam" << endl;
	      spam = spam + 1.0;
	    }
	}
      else if (isInfo > isSport)
	{
	  if (checkclass == '0')
	    {
	      //cout << "adding one to ham" << endl;
	      ham = ham + 1.0;
	    }
	}
    }
  
  // cout << "\nSuccessful detection rate of " << spam/ignore1 * 100 << "% " << ham/ignore2 * 100 << '%' << endl;
  cout << "Successful detection rate of " << ((spam + ham)/evaluate) * 100 << '%' << endl;
  //cout << "Spam: " << spam << " ignore1: " << ignore1 << " ignore2: " << ignore2 << endl;
  
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


