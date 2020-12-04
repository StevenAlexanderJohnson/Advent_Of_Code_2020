#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int Partition(vector<int> &list, int lowIndex, int highIndex)
{
	int pivot = list[highIndex];
	int i = lowIndex - 1;
	
	int temp;
	for(int j = lowIndex; j <= highIndex - 1; j++)
	{
		if(list[j] < pivot)
		{
			i++;
			temp = list[i];
			list[i] = list[j];
			list[j] = temp;
		}
	}
	temp = list[i+1];
	list[i+1] = list[highIndex];
	list[highIndex] = temp;
	return (i + 1);
}

void QuickSort(vector<int> &list, int lowIndex, int highIndex)
{
	if(lowIndex < highIndex)
	{
		int partitionIndex = Partition(list, lowIndex, highIndex);
		
		QuickSort(list, lowIndex, partitionIndex - 1);
		QuickSort(list, partitionIndex + 1, highIndex);
	}
}

int main()
{
	// Creating file stream for input text file.
	ifstream inputFile ("Day1Input.tt");
	
	// If file opens correctly run code otherwise tell user.
	if(inputFile.is_open())
	{
		// String variable to hold each line of the text file.
		string line;
		// Load numbers into vector.
		vector<int> input = vector<int>();
		while(getline(inputFile, line))
		{
			input.push_back(stoi(line));
		}
		
		QuickSort(input, 0, input.size()-1);
		
		for(auto value: input)
		{
			cout << value << " ";
		}
		cout << endl;

		for(vector<int>::iterator end = input.end(); end != input.begin(); end--)
		{
			for(vector<int>::iterator begin = input.begin(); begin != end; begin++)
			{
				if(*begin + *end > 2020)
				{
					cout << "breaking" << endl;
					break;
				}
				if(*begin + *end == 2020)
				{
					cout << *begin << " " << *end << endl;
					cout << *begin + *end << endl;
					return 0;
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
