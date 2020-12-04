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
	// Opening the input file.
	ifstream inputFile ("Day1Input.txt");
	
	// If the file opens correctly run code, otherwise alert user.
	if(inputFile.is_open())
	{
		int test = 0;
		string line;
		vector<int> input = vector<int>();
		// While there are lines to read push the values into the vector.
		while(getline(inputFile, line))
		{
			input.push_back(stoi(line));
		}
		
		// Sorting to get the smallest values first
		QuickSort(input, 0, input.size()-1);
		
		// Looping through to find three values whose sum is 2020.
		for(vector<int>::iterator first = input.begin(); first != input.end()-2; first++)
		{
			for(vector<int>::iterator second = first+1; second != input.end()-1; second++)
			{
				if(*first + *second >= 2020)
				{
					continue;
				}
				for(vector<int>::iterator third = second+1; third != input.end(); third++)
				{
					if(*first + *second + *third == 2020)
					{
						cout << *first << ", " << *second << ", " << *third << " = " << *first * *second * *third << endl;
						return 1;
					}
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
