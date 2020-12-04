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
		int right = 0;
		int numberOfTrees = 0;
		for(int down = 0; down < map.size(); down += 2)
		{
			if(map[down].substr(right,1) == "#")
			{
				numberOfTrees += 1;
			}
			right += 1;
		}
		/*for(int down = 0; down < map.size(); down++)
		{
			if(map[down].substr(right,1) == "#")
			{
				numberOfTrees += 1;
			}
			right += 3;
		}*/
		cout << numberOfTrees << endl;
	}
	else
	{
		cout << "File could not be opened." << endl;
		return -1;
	}
	return 0;
}
