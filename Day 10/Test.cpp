#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

int Partition(vector<unsigned long long> &list, int lowIndex, int highIndex)
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

void QuickSort(vector<unsigned long long> &list, int lowIndex, int highIndex)
{
	if(lowIndex < highIndex)
	{
		int partitionIndex = Partition(list, lowIndex, highIndex);
		
		QuickSort(list, lowIndex, partitionIndex - 1);
		QuickSort(list, partitionIndex + 1, highIndex);
	}
}

unsigned long long DFSHelper(vector<unsigned long long> inputVector, vector<int> &visited, int vertex)
{	
	if(visited[vertex] != 0)
	{
		return visited[vertex];
	}
	if(vertex == inputVector.size()-1)
	{
		return 1;
	}
	
	for(int i = vertex + 1; i < inputVector.size(); i++)
	{
		if(inputVector[i] - inputVector[vertex] >= 1 && inputVector[i] - inputVector[vertex] <= 3)
		{
			visited[vertex] += DFSHelper(inputVector, visited, i);
			/*for(int k: visited)
			{
				cout << k << "  ";
			}
			cout << endl;*/
		}
		else
		{
			break;
		}
	}
	return visited[vertex];
}

unsigned long long DepthFirstSearch(vector<unsigned long long> &inputVector)
{
	vector<int> visited(inputVector.size(), 0);
	
	for(int i = 0; i < inputVector.size(); i++)
	{
		cout << i << ": " << inputVector[i] << endl;
	}
	cout << endl;
	DFSHelper(inputVector, visited, 0);
	return visited[0];
}

int main()
{
	// Creating file reader.
	ifstream inputFile("Input.txt");
	// Creating vector to hold numbers from input file.
	vector<unsigned long long> input;
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
	
	int validPossibilities;
	
	validPossibilities = DepthFirstSearch(input);
	
	//cout << "Answer: " << validPossibilities;
	
	return 0;
}
