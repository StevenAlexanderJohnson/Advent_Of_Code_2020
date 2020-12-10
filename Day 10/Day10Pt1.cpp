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
	
	ifstream inputFile("Input.txt");
	vector<int> input;
	string line;
	
	while(getline(inputFile, line))
	{
		input.push_back(stoi(line));
	}
	
	QuickSort(input, 0, input.size()-1);
	
	input.push_back(input[input.size()-1] + 3);
	
	/*for(auto x: input)
	{
		cout << x << endl;
	}*/
	
	int oneJolt = 0;
	int twoJolt = 0;
	int threeJolt = 0;
	int currentAdapter = 0;
	
	for(int i = 0; i < input.size(); i++)
	{
		switch(input[i] - currentAdapter)
		{
			case 1:
				currentAdapter = input[i];
				oneJolt++;
				break;
			case 2:
				currentAdapter = input[i];
				twoJolt++;
				break;
			case 3:
				currentAdapter = input[i];
				threeJolt++;
				break;
			default:
				cout << "Error: " << input[i] << " - " << input[i-0] << 
					  	" = " << input[i] - input[i - 1] << endl;
				break;
		}
	}
	cout << "One Jolt: " << oneJolt << " Three Jolt: " << threeJolt << endl;
	cout << oneJolt * threeJolt << endl;
	return 0;
}
