#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	// Creating file reader.
	ifstream inputFile("Input.txt");
	
	// If the file is opened correctly run the code.
	if(inputFile.is_open())
	{
		// Vector to hold all the boardingPasses.
		vector<string> boardingPasses;
		// String to hold the line value.
		string line;
		//While there are lines to read in the file read them.
		while(getline(inputFile, line))
		{
			// Add the boarding pass to the boardingPasses vector.
			boardingPasses.push_back(line);
		}
		
		// Highest value found.
		int highestValue = 0;
		
		// Variable for the lower end of the range.
		int lowRange = 0;
		// Variable for the higher end of the range.
		int highRange = 127;
		
		// Variable for the left end of the range.
		int leftRange = 0;
		// Variable for the right end of the range.
		int rightRange = 7;
		
		// Loop over every pass in boardingPasses.
		for(auto pass: boardingPasses)
		{
			// Loop over every letter in the boarding pass.
			for(char letter: pass)
			{
				// If the letter is F then the high range is changed to be in the middle of the range.
				if(letter == 'F')
				{
					highRange = int((lowRange + highRange)/2);
				}
				// Else if the letter is B the lower range is set the be the middle of the range.
				else if(letter == 'B')
				{
					lowRange = int((lowRange + highRange)/2)+1;
				}
				
				// Else if the letter is L then the right range is set the middle of the range.
				else if(letter == 'L')
				{
					rightRange = int((leftRange + rightRange)/2);
				}
				// Else if the letter is R then the left range is set to the mide of the range.
				else if(letter == 'R')
				{
					leftRange = int((leftRange + rightRange)/2)+1;
				}
			}
			
			// If the high range doesn't equal the low range then there was an error. Ditto for left and right.
			if(highRange != lowRange || leftRange != rightRange)
			{
				cout << "Error in calculation." << endl;
				return -1;
			}
			
			// Check if (row * 8) + column is greater than the previous highest value.
			if(highestValue < (highRange * 8) + rightRange)
			{
				highestValue = (highRange * 8) + rightRange;
			}
			
			// Reset all of the ranges.
			highRange = 127;
			lowRange = 0;
			leftRange = 0;
			rightRange = 7;
		}
		// Print out the highest value.
		cout << highestValue << endl;
		return 999;
	}
	else
	{
		cout << "Could not open file." << endl;
		return -1;
	}
	
	return 0;
}
