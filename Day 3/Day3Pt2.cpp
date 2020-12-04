#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	// Setting console color green to look like *HACKERMAN*... or trees.
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	ifstream inputFile("Input.txt");
	
	if(inputFile.is_open())
	{
		// Loading the map input from the file into the map vector.
		vector<string> map;
		string line;
		// While there are lines to read push them into the vector.
		while(getline(inputFile, line))
		{
			map.push_back(line);
		}
		
		// To have a slope of three right one down, to reach the bottom of the map
		// the width has to be 3 times the height.
		int width = map.size()*7;
		// For every string, append it to itself until it is wide enought to traverse.
		for(int i = 0; i < map.size(); i++)
		{
			while(map[i].size() < width)
			{
				map[i] += map[i];
			}
		}
		
		// Looping until I reach the bottom level of the map.
		int row = 0;
		int column = 0;
		int twoSlopeTrees = 0;
		int oneMultiple = 0;
		int oneMultipleTrees = 0;
		int threeMultiple = 0;
		int threeMultipleTrees = 0;
		int fiveMultiple = 0;
		int fiveMultipleTrees = 0;
		int sevenMultiple = 0;
		int sevenMultipleTrees = 0;
		unsigned long int numberOfTrees = 0;
		while(row < map.size())
		{
			if(map[row].substr(oneMultiple, 1) == "#")
			{
				oneMultipleTrees += 1;
			}
			oneMultiple += 1;
			if(map[row].substr(threeMultiple, 1) == "#")
			{
				threeMultipleTrees += 1;
			}
			threeMultiple += 3;
			if(map[row].substr(fiveMultiple, 1) == "#")
			{
				fiveMultipleTrees += 1;
			}
			fiveMultiple += 5;
			if(map[row].substr(sevenMultiple, 1) == "#")
			{
				sevenMultipleTrees += 1;
			}
			sevenMultiple += 7;
			
			row += 1;
		}
		
		int right = 0;
		for(int down = 0; down < map.size(); down += 2)
		{
			if(map[down].substr(right,1) == "#")
			{
				twoSlopeTrees += 1;
			}
			right += 1;
		}
		
		cout << oneMultipleTrees << " " << threeMultipleTrees << " " << fiveMultipleTrees << " " << sevenMultipleTrees << " " << twoSlopeTrees << endl;
		numberOfTrees = oneMultipleTrees * threeMultipleTrees * fiveMultipleTrees * sevenMultipleTrees * twoSlopeTrees;
		cout << numberOfTrees << endl;
	}
	else
	{
		cout << "File could not be opened." << endl;
		return -1;
	}
	return 0;
}
