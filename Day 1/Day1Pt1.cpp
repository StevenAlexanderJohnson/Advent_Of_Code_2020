#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	ifstream inputFile ("Day1Input.txt");
	if(inputFile.is_open())
	{
		string line;
		vector<int> input = vector<int>();
		while(getline(inputFile, line))
		{
			input.push_back(stoi(line));
		}
		vector<int>::iterator begin;
		for(begin = input.begin(); begin != input.end(); begin++)
		{
			for(vector<int>::iterator next = begin++; next != input.end(); next++)
			{
				if(*begin + *next == 2020)
				{
					cout << *begin * *next << endl;
					return 1;
				}
			}
		}
	}
	else
	{
		cout << "Could not open file." << endl;
	}
	return 0;
}
