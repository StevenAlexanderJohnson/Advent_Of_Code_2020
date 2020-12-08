#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int main()
{
	// Creating input file stream to read input.
	ifstream inputFile("Input.txt");
	
	// If the file is opened correctly run the code, else exit.
	if(inputFile.is_open())
	{
		// Create two maps to hold the alphabet. First to get keep track of the input
		// and the second to be kept as a constant to reassign the first.
		map<char, int> alphabet;
		map<char, int> alphabetConst;

		// Creating the map.
		for(int i = 97; i <= 122; i++)
		{
			char character = i;
			alphabet.insert(pair<char, int>(char(i), 0));
		}
		// Giving constant alphabet its value.
		alphabetConst = alphabet;
		
		// vector to hold the value of the line describing whole loop.
		vector<string> inputLines;
		// String value to hold line value of individual.
		string line;
		// Int value to describe how many people are in the group.
		int groupMembers = 0;
		// String value to be put into the inputLines vector.
		string concatenatedLine;
		
		// While there are lines to be read, read them and run the code.
		while(getline(inputFile, line))
		{
			stringstream ss;
			// If the reader has reached the end of the file, add line to the concatenated
			// string and push it into the vector.
			if(inputFile.eof())
			{
				groupMembers += 1;
				ss << groupMembers;
				concatenatedLine = ss.str() + concatenatedLine + line;
				inputLines.push_back(concatenatedLine);
				groupMembers = 0;
			}
			// Else if the line is empty that means that it has moved onto a different group.
			// Push the current value into the vector.
			else if(line.empty())
			{
				ss << groupMembers;
				concatenatedLine = ss.str() + concatenatedLine;
				inputLines.push_back(concatenatedLine);
				concatenatedLine.clear();
				groupMembers = 0;
			}
			// Else means that the group is still being read so add the value to the concatenated
			// string.
			else
			{
				concatenatedLine += line;
				groupMembers += 1;
			}
		}
		
		// Adding up the number of questions answered yes.
		int count = 0;
		// For each string representation of the group,
		for(int i = 0; i < inputLines.size(); i++)
		{
			// Setting string variable to clean code.
			line = inputLines[i];
			// Setting groupMembers Variable to use as a check.
			groupMembers = stoi(line.substr(0,1));
			
			// For each character in that string, set the value to true.
			for(int j = 1; j < inputLines[i].size(); j++)
			{
				alphabet[line[j]] += 1;
			}
			
			// Checking each letter of the alphabet to see if it is set
			// true.
			for(auto letter: alphabet)
			{
				if(letter.second == groupMembers)
				{
					count += 1;
				}
			}
			// Assigning the alphabet back to the constant value.
			alphabet = alphabetConst;
		}
		
		// Print how many true values there are and return my ending number.
		cout << count;
		return 999;
	}
	else
	{
		cout << "Could not open file." << endl;
		return -1;
	}
	
	return 0;
}
