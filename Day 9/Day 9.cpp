#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/* * * * * * * * Quick Sort * * * * * * * */
void swap(unsigned long long* a, unsigned long long* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(vector<unsigned long long> &vectorInput, unsigned long long low, unsigned long long high)
{
	int pivot = vectorInput[high];
	int smallIndex = low - 1;
	
	for(int i = low; i <= high - 1; i++)
	{
		if(vectorInput[i] <= pivot)
		{
			smallIndex++;
			swap(&vectorInput[smallIndex], &vectorInput[i]);
		}
	}
	swap(&vectorInput[smallIndex + 1], &vectorInput[high]);
	return smallIndex + 1;
}

void QuickSort(vector<unsigned long long> &inputVector, int low, int high)
{
	if(low < high)
	{
		int partitionIndex = partition(inputVector, low, high);
		
		QuickSort(inputVector, low, partitionIndex - 1);
		QuickSort(inputVector, partitionIndex + 1, high);
	}
}
/* * * * * * * * * * * * * * * * * * * * * */

void PrintVector(vector<unsigned long long> vectorInput)
{
	for(auto x: vectorInput)
	{
		cout << x << endl;
	}
}

int main()
{
	// Creating file reader.
	ifstream inputFile("Input.txt");
	
	// If the input file is opened correctly.
	if(inputFile.is_open())
	{
		cout << "File Opened" << endl;
		// Vector to hold the file input.
		vector<unsigned long long> input;
		// String to hold the value of the line.
		string line;
		
		// While there are lines to read in the file read it.
		while(getline(inputFile, line))
		{
			// Push the line into the input vector.
			input.push_back(stoull(line));
		}
		
		// Change the size of the preamble.
		int preamble = 25;
		
		// Index iterating variable.
		int chunkIndex = 0;
		// End value of the chunk.
		int endValue = chunkIndex + preamble - 1;
		// Vector to hold the preamble.
		vector<unsigned long long> preambleVector;
		// Creating a infident loop.
		while(true)
		{
			// Clear to the preamble vector.
			preambleVector.clear();
			// Variable that will signal that it has reached the end of the input.
			endValue = chunkIndex + preamble - 1;
			
			// If the end of the list reached it will break the loop.
			if(endValue > input.size())
			{
				break;
			}
			// Push all of the chunk into the preamble vector.
			for(int i = chunkIndex; i <= endValue; i++)
			{
				preambleVector.push_back(input[i]);
			}
			
			// Quick sort the preamble vector.
			QuickSort(preambleVector, 0, preambleVector.size()-1);

			// Value of the sum value.
			int sumIndex = chunkIndex + preamble;
			// Value of the largest number in the preamble vector.
			int highValue = preambleVector.size() - 1;
			// Value of the smallest number in the preamble vector.
			int lowValue = 0;
			// Continuesly loop until it is broken.
			while(true)
			{
				// If the two checked values equal the sum, break the loop.
				if(preambleVector[lowValue] + preambleVector[highValue] == input[sumIndex])
				{
					break;
				}
				// If none of the numbers the list sum to the sum value, print out the answer.
				else if(lowValue == highValue)
				{
					cout << "Answer: " << input[sumIndex];
					return 999;
				}
				// If the sum it to small increment the small value.
				else if(preambleVector[lowValue] + preambleVector[highValue] < input[sumIndex])
				{
					lowValue++;
				}
				// If the sum is to large deincrement the large value.
				else if(preambleVector[lowValue] + preambleVector[highValue] > input[sumIndex])
				{
					highValue--;
				}
			}
			
			// Roll over to the next chunk.
			chunkIndex++;
		}
	}
	else
	{
		cout << "Could not open file." << endl;
		return -1;
	}
	
	
	return 998;
}
