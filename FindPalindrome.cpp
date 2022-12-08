#include <string>
#include <vector>
#include <iostream>
#include <locale> 
#include "FindPalindrome.hpp"

using namespace std;

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

// helper function to convert string to lower case
static void convertToLowerCase(string & value)
{
	locale loc;
	for (int i=0; i<value.size(); i++) {
		value[i] = tolower(value[i],loc);
	}
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(vector<string>
        candidateStringVector, vector<string> currentStringVector)
{
	string temp_word; 

	vector<string> temp_cand; 
	vector<string> temp_current; 

	if(currentStringVector.size() == 0)
	{	
		temp_cand = candidateStringVector; 

		// converting string elements in candidate string vector to a word
		for(int i=0; i< candidateStringVector.size(); i++)
		{
			convertToLowerCase(temp_cand[i]);
			temp_word = temp_word+temp_cand[i]; 
		}
		
		// if candidate vector is a palindrome, store this vector in current vector
		if(isPalindrome(temp_word))
			currVector.emplace_back(candidateStringVector);
	}
	
	for( int i=0; i< currentStringVector.size(); i++)
	{
		// storing candidate and current vectors in temporary vectors
		temp_cand = candidateStringVector;
		temp_current = currentStringVector;

		// lowercasing temporary candidate and current vector
		for(int i=0; i< temp_cand.size(); i++)
		{
			convertToLowerCase(temp_cand[i]);
		}

		for(int i=0; i< temp_current.size(); i++)
		{
			convertToLowerCase(temp_current[i]);
		}

		//adding string from currentString to candidate String
		temp_cand.emplace_back(temp_current[i]);
		temp_current.erase(temp_current.begin() + i); 

		//recursion with cutTest
		if(cutTest2 (temp_cand, temp_current))
			recursiveFindPalindromes(temp_cand, temp_current); 
		else
			temp_cand.clear();
			temp_current.clear(); 
	}
}

// private function to determine if a string is a palindrome (given, you
// may change this if you want)
bool FindPalindrome::isPalindrome(string currentString) const
{
	locale loc;
	// make sure that the string is lower case...
	convertToLowerCase(currentString);
	// see if the characters are symmetric...
	int stringLength = currentString.size();
	for (int i=0; i<stringLength/2; i++) {
		if (currentString[i] != currentString[stringLength - i - 1]) {
			return false;
		}
	}
	return true;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
	currVector.resize(0);
	candVector.resize(0);
}

FindPalindrome::~FindPalindrome()
{
	currVector.clear();
	candVector.clear();
}

int FindPalindrome::number() const
{
	return currVector.size();
}

void FindPalindrome::clear()
{
	candVector.clear();
	currVector.clear();
}

bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
	//vector temp_string to use locally in the cutTest1 member. 
	vector<string> tempStringVector = stringVector; 

	//frequency array that stores the number of times each character a-z appears in stringVector
	int frequency[26] = {0};

	//for loop that iterates for each element of frequency vector
	for(int k = 0; k<27 ; k++)
	{
		//count value to store the frequency of each letter
		int count = 0; 

		int size = tempStringVector.size(); 

		//for loop to iterate through all words of stringVector
		for( int i = 0; i < size; i++)
		{
			//converting vector to lower case
			convertToLowerCase ( tempStringVector[i]);
			//size of current word
			int wordSize = tempStringVector[i].size(); 

			//for loop to step through the word to get frequency of current letter
			for(int j=0; j< wordSize; j++)
			{
				char currCharacter = tempStringVector[i][j]; 

				if( currCharacter == 'a'+k)
				{
					count++;
					frequency[k] = count; 
				}
			}	
		}
	}

	//temp count variable
	int EvenCount=0; 

	//for loop to step through frequency array
	for( int i=0; i<27; i++)
	{
		//count number of odd character frequency
		if(frequency[i] %2 != 0)
		{
			EvenCount++;
		}
	}

	//because the frequency of every single letter can only be even
	//if there is an odd number of times a letter appears it can only be the center character
	//therefore, if count is greater than one stringVector fails cutTest1
	if(EvenCount > 1)
	{
		return false;
	}
	

	return true;
}

bool FindPalindrome::cutTest2(const vector<string> & stringVector1,
                              const vector<string> & stringVector2)
{
	//vectors of type string left and right
	vector<string> left; 
	vector<string> right; 

	//making left vector be smaller or equal in length
	if(stringVector1.size() >= stringVector2.size())
	{
		right = stringVector1;
		left = stringVector2;  
	}
	else
	{
		left = stringVector1; 
		right = stringVector2; 
	}



	//checking if all chars in left are in right
	//for loop stepping through each word in vector left
	for(int i=0; i < left.size(); i++)
	{
		convertToLowerCase(left[i]);

		int word_size = left[i].size(); 

		

		//for loop stepping through each letter in each word in vector left
		for(int j = 0; j < word_size; j++)
		{
			int step_begin = 0;
			int count= 0; 

			//while loop that scans the entire right vector of strings
			while( step_begin < right.size())
			{

				//for loop with variable k as index of the characters in strings of right vector
				for(int k=0; k< right[step_begin].size(); k++)
				{
					if(left[i][j] == right[step_begin][k])
						count++; 
				}
				step_begin++; 
			}

			//if count variable not increased return false
			if(count == 0)
			return false; 
		}

		
	}


	return true;
}


bool FindPalindrome::add(const string & value)
{
	string curr_val = value; 
	vector<string> temp_candidate = candVector;

	convertToLowerCase(curr_val);

	//ensuring that input is alphabetical
	for( int i=0; i < curr_val.size(); i++)
	{

		if(! (curr_val[i] >= 'a' && curr_val[i] <= 'z' ) )
			return false; 

	} 

	//for loop checking if value was already added in candidate vector
	for( int i =0; i< temp_candidate.size(); i++)
	{
		convertToLowerCase(temp_candidate[i]); 
		if( curr_val == temp_candidate[i])
			return false; 
	}

	//if there is no existed value, value pushed back into candidate vector
	candVector.emplace_back(value); 

	if(cutTest1 (candVector))
	{
		currVector.clear(); 
		recursiveFindPalindromes({}, candVector); 
	}
	else
		currVector = {}; 
	return true;
}


bool FindPalindrome::add(const vector<string> & stringVector)
{
	vector<string> temp_val = stringVector; 
	vector<string> temp_cand = candVector; 

	//valid string check
	for(int i =0; i < temp_val.size(); i++)
	{
		for(int j=0; j< temp_val[i].size(); j++)
		{
			convertToLowerCase(temp_val[i]);
			if( !( temp_val[i][j] >= 'a' && temp_val[i][j] <= 'z'))
			{
				return false; 
			}
		}

		//duplicate check
		convertToLowerCase(temp_val[i]);

		for( int j = 0; j < temp_cand.size(); j++)
		{
			convertToLowerCase(temp_cand[j]);

			if(temp_val[i] == temp_cand[j])
				return false; 
		}

		candVector.insert(std::end(candVector),std::begin(stringVector), std::end(stringVector));

		if(cutTest1(candVector))
		{
			recursiveFindPalindromes({}, candVector);
		}
		else
			currVector = {{}};

		return true; 

	}


	return true;
}

vector< vector<string> > FindPalindrome::toVector() const
{
	return currVector;
}

vector<string> FindPalindrome::getCandVector() const
{
	return candVector;
}
