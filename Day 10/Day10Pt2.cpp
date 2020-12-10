#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

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
	// Creating file reader.
	ifstream inputFile("Input.txt");
	// Creating vector to hold numbers from input file.
	vector<int> input;
	// String Variable that holds the value of the line of the file.
	string line;
	
	// While there are lines to read in the file push the value into the input vector.
	while(getline(inputFile, line))
	{
		input.push_back(stoi(line));
	}
	
	// Sort the input from least to greatest value.
	QuickSort(input, 0, input.size()-1);
	
	// Add the jolt difference of the device.
	input.push_back(input[input.size()-1] + 3);
	input.insert(input.begin(), 0);
	
	/*for(auto x: input)
	{
		cout << x << endl;
	}*/
	
	// Value to hold the index of the current adapter being checked.
	int currentAdapter = 0;
	// Answer value to hold the valid number of orientations.
	int validCount = 0;
	// Stack to hold all index of the next number to be checked as current adapter.
	stack<int> validStack;
	// Adding the first index to the stack.
	validStack.push(0);
	
	// While the stack isn't empty run.
	while(!validStack.empty())
	{
		//Get the value of the current adapter being checked.
		currentAdapter = validStack.top();
		validStack.pop();
		int validStackSize = validStack.size();
		//cout << validStackSize << endl;
		
		if(input[currentAdapter] == input[input.size()-1])
		{
			validCount++;
			if(validCount % 100000 == 0)
			{
				cout << validCount << endl;
			}
			continue;
		}
		
		for(int i = currentAdapter+1; i < input.size(); i++)
		{
			if(input[i] - input[currentAdapter] >= 1 && input[i] - input[currentAdapter] <= 3)
			{
				validStack.push(i);
			}
			else
			{
				break;
			}
		}
	}
	
	cout << "Answer: " << validCount << endl;
	
	return 0;
}
