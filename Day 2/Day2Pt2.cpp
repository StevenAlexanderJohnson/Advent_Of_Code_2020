#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
	ifstream inputFile("Input.txt");
	vector<string> numbers;
	vector<string> letter;
	vector<string> password;
	
	// If input file is not opened correctly tell the user and end.
	if(inputFile.is_open())
	{
		// Varible to control the action taken by the switch.
		int switchCase = 1;
		// Variable the line from the text file is saved in.
		string line;
		//While there are lines in the text file to read, read them.
		while(getline(inputFile, line))
		{
			// Break the line into words.
			istringstream iss(line);
			
			// While there are words in the stream, put them into the correct vector.
			do
			{
				string subs;
				
				// Assign the word to substring variable.
				iss >> subs;
				switch(switchCase)
				{
					case 1:
						numbers.push_back(subs);
						switchCase = 2;
						break;
					case 2:
						letter.push_back(subs.substr(0,1));
						switchCase = 3;
						break;
					case 3:
						password.push_back(subs);
						switchCase = 4;
						break;
					case 4:
						switchCase = 1;
						break;
				}
			}
			while(iss);
		}
		
		// Checking if vectors were loaded correctly.
		if(numbers.size() != letter.size() || numbers.size() != password.size())
		{
			cout << "Error loading vectors." << endl;
			return 1;
		}
		
		// Since all vectors are the same length I can just iterate over one.
		// Loop over a numbers and find valid passwords.
		int validPasswords = 0;
		for(int i = 0; i < numbers.size(); i++)
		{
			// Parse the number string into numbers.
			string firstNumberString = numbers[i].substr(0, numbers[i].find("-"));
			int secondNumber = stoi(numbers[i].substr(firstNumberString.size()+1));
			int firstNumber = stoi(firstNumberString);
			
			// Getting value of the letter to check.
			char letterCheck = *letter[i].c_str();
			// Getting value of the string to check.
			string passwordCheck = password[i];
			
			// If only one of the two positions returns true then it is a valid password.
			if(passwordCheck[firstNumber-1] == letterCheck ^ passwordCheck[secondNumber-1] == letterCheck)
			{
				validPasswords++;
			}
		}
		
		cout << validPasswords << endl;
		return 420;
	}
	else
	{
		cout << "Could not open file." << endl;
	}
	return 0;
}
