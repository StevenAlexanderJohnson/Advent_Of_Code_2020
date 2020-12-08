#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

int main()
{
	// Create the file reader.
	ifstream inputFile("Input.txt");
	
	// If the file is opened correctly run the code.
	if(inputFile.is_open())
	{
		// Variable to hold the line value.
		string line;
		// Variable to hold line number to create the map.
		int lineNumber = 0;
		// Vector to hold all the line strings.
		vector<string> lines;
		// Map to keep track if the line has been visited before.
		map<int, bool> lineMap;
		
		// output value for the acc.
		int acc = 0;
		
		// While there are lines to read, add the line number to the map and the line value vector.
		while(getline(inputFile, line))
		{
			lineMap.insert(pair<int, bool>(lineNumber, false));
			lines.push_back(line);
			lineNumber++;
		}
		
		// Reset lineNumber to 0 so that I can use it to check the map.
		lineNumber = 0;
		// String to hold the function the line is doing.
		string function;
		// String to hold the operation the number is doing.
		string operation;
		
		// Continuesly loop until terminated.
		while(true)
		{
			// If the line number has been visited before return the acc value.
			if(lineMap[lineNumber])
			{
				cout << "Line Repeated: " << lineNumber + 1 << endl;
				cout << "acc value: " << acc << endl;
				break;
			}
			// Get the function the line is doing.
			function = lines[lineNumber].substr(0,3);
			// If it is nop then set line to visited and go to next line.
			if(function == "nop")
			{
				lineMap[lineNumber] = true;
				lineNumber++;
				continue;
			}
			// Get the operation the number is doing.
			operation = lines[lineNumber].substr(4,1);
			// If the function is acc add or subtract the number from acc.
			if(function == "acc")
			{
				lineMap[lineNumber] = true;
				if(operation== "-")
				{
					acc -= stoi(lines[lineNumber].substr(5));
					lineNumber++;
				}
				else if(operation == "+")
				{
					acc += stoi(lines[lineNumber].substr(5));
					lineNumber++;
				}
				// If the operation is neither there was an error.
				else
				{
					cout << "Error in acc function check. Value: " << operation <<  endl;
					return -1;
				}
			}
			// If the function is jmp then add or subtract the number value from the line number.
			else if(function == "jmp")
			{
				lineMap[lineNumber] = true;
				if(operation == "-")
				{
					lineNumber -= stoi(lines[lineNumber].substr(5));
				}
				else if(operation == "+")
				{
					lineNumber += stoi(lines[lineNumber].substr(5));
				}
				// If the operation is neither then there was an error.
				else
				{
					cout << "Error in jmp function check. Value:" << operation << endl;
					return -1;
				}
			}
		}
		
		inputFile.close();
		return 999;
	}
	else
	{
		cout << "Could not open file." << endl;
		return -1;
	}
	return 0;
}
