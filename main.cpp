#include "Header.h"
#include <iostream>
#include <fstream>

const int TOTAL_PHRASE = 5000;
const int MAX_WORDS = 6;

int linearSearch(MyString s[], MyString keyWords, int size)
{

	for (int i = 0; i < size; i++)
	{
		if(s[i] == keyWords)
			return i ;
	}
	return -1;
}

void swap(MyString& i, MyString& j)
{
	MyString temp;
	temp = i;
	i = j;
	j = temp;
}

void selectSort(MyString s[], int size, bool ascending)
{
	MyString minString;
	int minIndex;

	for (int start = 0; start < (size - 1); start++)
	{
		minIndex = start;
		minString = s[start];
		for (int index = start + 1; index < size; index++)
		{
			if (ascending)
			{
				if (s[index] < minString)
				{
					minString = s[index];
					minIndex = index;
				}
			}
			else
			{
				if (s[index] > minString)
				{
					minString = s[index];
					minIndex = index;
				}
			}
		}
		swap(s[minIndex], s[start]);
	}
}

int main()
{
	string infileName, outfileName;
	ifstream inFile;
	ofstream outFile;

	MyString word[MAX_WORDS];
	MyString phrase[TOTAL_PHRASE];

	int n;

	cout << "Enter the source data file: " ;
	cin >> infileName;
	cout << "How many Adjacent words in a phrase: ";
	cin >> n;
	cout << "Enter the phrase frequency file name: ";
	cin >> outfileName;

	int j = 0, k = 0;
	int wordCount = 0;
	int phraseCount = 0;
	MyString temp, dummy;

  //opening the file and reading it
	inFile.open(infileName);
	while ((!inFile.eof()) && (j < (n - 1)))
	{
		inFile >> temp;
		if(!(temp == dummy))
		{
			word[j] = temp;
			j += 1;
			wordCount += 1;
		}
	}

  //while the file (eof) end of file then run this
	while (!inFile.eof())
	{
		MyString keyWords;
		inFile >> temp;
		if(!(temp == dummy))
		{
			word[j] = temp;
			wordCount += 1;
      //combining words together and making it become keywords.
			for (int i = 0; i < n; i++) {
        //having the word[i] means that all the words in the array are uppercased before combined
        word[i].ToUpper();
				keyWords = keyWords + word[i];
      }
      //using linearsearch if the phrase is already there, and if it is then we increment if not then phrase[k]++
			k = linearSearch(phrase, keyWords, phraseCount);
			if(k == -1)
			{
				phrase[phraseCount] = keyWords;
				phraseCount++;
			}
			else
			{
				phrase[k]++;
			}
			for (int i = 1; i < n; i++)
				word[i - 1] = word[i];
		}
	}

	inFile.close();

  //if the wordcount is less than the number that the user put it then the file is too short
	if (wordCount < n)
	{
		cout << "The file is empty or too short " << endl;
		exit(0);
	}

	selectSort(phrase, phraseCount, false);

	outFile.open(outfileName);

  //printing out the top part of the code
	outFile << "The file " << outfileName << " contains " << wordCount << " Words." << endl;
  outFile << "There are " << phraseCount << " unique terms" << '\n' << endl;

	for (int j = 0; j < phraseCount; j++)
		outFile << phrase[j] << endl;

	outFile.close();

	return 0;
}

