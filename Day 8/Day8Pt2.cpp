#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

bool Terminates(map<int, bool> lineMap, vector<string> lines)
{
	// Variable to hold the acc value.
	int acc = 0;
	// Line Number variable used to create the map.
	int lineNumber = 0;
	// String variables to that holds what function is at the start
	// of the line.
	string function;
	// String variable that holds what operation is before the number.
	string operation;
	
	// Continuesly loop until one of the if statements ends the loop.
	while(true)
	{
		// If the line number reaches the end of the list then it terminates.
		if(lineNumber == lines.size())
		{
			cout << "Terminated: " << acc << endl;
			return true;
		}
		// if the line number has been reached before it is a loop.
		if(lineMap[lineNumber])
		{
			return false;
		}
		
		// Captureing what function the line us using.
		function = lines[lineNumber].substr(0,3);
		
		// If the function is nop go to next line.
		if(function == "nop")
		{
			lineMap[lineNumber] = true;
			lineNumber++;
			continue;
		}
		
		// Capturing what operation this line is doing to the acc or line number.
		operation = lines[lineNumber].substr(4,1);
		
		// If the function is acc,
		if(function == "acc")
		{
			// Set line visited variable to true.
			lineMap[lineNumber] = true;
			// If the operation is - then subtract the number value from acc.
			if(operation== "-")
			{
				acc -= stoi(lines[lineNumber].substr(5));
				lineNumber++;
			}
			// Else if add the number value to acc.
			else if(operation == "+")
			{
				acc += stoi(lines[lineNumber].substr(5));
				lineNumber++;
			}
			// Else return the error.
			else
			{
				cout << "Error in acc function check. Value: " << operation <<  endl;
				return -1;
			}
		}
		// Else if the function is jmp,
		else if(function == "jmp")
		{
			// Set line visited variable to true.
			lineMap[lineNumber] = true;
			// If the operation is - subtract the number value from lineNumber.
			if(operation == "-")
			{
				lineNumber -= stoi(lines[lineNumber].substr(5));
			}
			// Else if the operation is + add the number value to lineNumber.
			else if(operation == "+")
			{
				lineNumber += stoi(lines[lineNumber].substr(5));
			}
			// Else return error
			else
			{
				cout << "Error in jmp function check. Value:" << operation << endl;
				return -1;
			}
		}
	}
}

int main()
{
	// Creating file reader.
	ifstream inputFile("Input.txt");
	
	// If file opened correctly run code.
	if(inputFile.is_open())
	{
		// Variable to hold line value.
		string line;
		// Variable to hold the line number to create the map.
		int lineNumber = 0;
		// Vector to hold all the lines.
		vector<string> lines;
		// Map used to determine if the line has been visited before.
		map<int, bool> lineMap;
		
		// While there are lines to read in the file read them.
		while(getline(inputFile, line))
		{
			// Create a value in the map for the line being read.
			lineMap.insert(pair<int, bool>(lineNumber, false));
			// Add the line to the lines vector.
			lines.push_back(line);
			// Increment the line number.
			lineNumber++;
		}
		
		// Vector to hold a copy of the lines vector so I can mutate it.
		vector<string> linesCopy;
		// Loop over the vector and switch each jmp with nop and each nop jmp one at a time.
		// If the switch doesn't work it gets changed back and the next one is switched.
		for(int i = 0; i < lines.size(); i++)
		{
			linesCopy = lines;
			if(linesCopy[i].substr(0,3) == "jmp")
			{
				linesCopy[i].replace(0,3, "nop");
			}
			else if(linesCopy[i].substr(0,3) == "nop")
			{
				linesCopy[i].replace(0,3, "jmp");
			}
			
			// If the switch makes the loop terminate then return success value;
			if(Terminates(lineMap, linesCopy))
			{
				// Close the input file.
				inputFile.close();
				return 999;
			}
		}
	}
	else
	{
		cout << "Could not open file." << endl;
		return -1;
	}
	
	return 0;
}
