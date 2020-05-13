// Assignment : Project 1
// File : similarity.hpp
// Author : Dr. Watts
// Description : This file contains an auxilary function
//               to determine the similarity between strings
//		 for Project 1.

#include <string>
#include <cctype>
using namespace std;

/* This function will determing the degree of similarity between 
   two strings.
   Pre-conditions: the user of the function will pass 2 strings
   as the arguments to the function.
   Post-conditions: The function will return a value between 0
   and 100 (inclusive) that indicates the degree of similarity.
   The strings passed to the function will not be modified. */

float similarity (const string & s1, const string & s2)
{
	float score = 0.0;
	int c1 [26], c2 [26];
	// Initialize letter counts to 0
	for (int i = 0; i < 26; i++)
		c1[i] = c2[i] = 0;
	int i = 0;
	// Scan common lengths of strings
	for (i = 0; i < s1.length() && i < s2.length(); i++)
	{
		if (s1[i] == s2[i])
		// Add one if characters are identical
			score += 1;
		else if (tolower(s1[i]) == tolower(s2[i]))
		// Add one half if letters are the same but 
		// different cases.
			score += 0.5;
		else 
		{
		// Add to letter counts for the words
			if (isalpha(s1[i]))
				c1[tolower(s1[i])-'a']++;
			if (isalpha(s2[i]))
				c2[tolower(s2[i])-'a']++;
		}
	}
	for (; i < s1.length(); i++)
		if (isalpha(s1[i]))
		// Add to letter counts for the rest of s1
			c1[tolower(s1[i])-'a']++;
	for (; i < s2.length(); i++)
		if (isalpha(s2[i]))
		// Add to letter counts for the rest of s2
			c2[tolower(s2[i])-'a']++;
	for (int i = 0; i < 26; i++)
	// Add one tenth of letter count for each letter with
	// identical counts.
		score += c1[i] == c2[i] ? 0.1 * c1[i] : 0;
	// Calculate and return similarity score
	return 200.0 * score / (s1.length() + s2.length());
}
