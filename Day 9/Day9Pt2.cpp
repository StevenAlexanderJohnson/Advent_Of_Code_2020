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

int main()
{
	// Create file reader.
	ifstream inputFile("Input.txt");
	
	// If the input file is opened correctly.
	if(inputFile.is_open())
	{
		// String to hold file line value.
		string line;
		// Vector to hold each line of the input.
		vector<unsigned long long> input;
		
		// Adding all the lines to the vector.
		while(getline(inputFile, line))
		{
			input.push_back(stoull(line));
		}
		
		// Expected value found from the previous question.
		unsigned long long iterateTo = 167829540;
		
		// Iterator I'm going to increment.
		int iterator = 0;
		// Iterator that I'm going to increment at the end of each loop.
		int iteratorCopy = 0;
		// Sum of all the numbers iterated over.
		unsigned long long sum = 0;
		// Vector to hold all values that are iterated over.
		vector<unsigned long long> sumVector;
		
		// Infident loop that only terminates when the code says so.
		while(true)
		{
			// Clear the sumVector from previous iterations.
			sumVector.clear();
			// Reset the iterator with the copy that should be one number higher
			// than the start of the previous number.
			iterator = iteratorCopy;
			
			// While the sum is smaller than the expected value,
			while(sum < iterateTo)
			{
				// Push all the numbers iterated over in sumVector.
				sumVector.push_back(input[iterator]);
				// Add the number to the sum value.
				sum += input[iterator];
				// Increment the iterator.
				iterator++;
			}
			
			// If the sum is not equal to the expected value, increment the start
			// point for the next iteration and reset the sum.
			if(sum != iterateTo)
			{
				iteratorCopy += 1;
				sum = 0;
			}
			// Else means that the sum equals the expected value.
			else if(sum == iterateTo)
			{
				// Sort the summed number vector.
				QuickSort(sumVector, 0, sumVector.size()-1);
				// Print out the answer using the first and last number of the vector.
				// Seeing it is sorted the first number is the smallest and the last is
				// the largest.
				cout << "Found" << endl << "Answer: " << sumVector[0] << " + ";
				cout << sumVector[sumVector.size()-1] << " = " << sumVector[0] + sumVector[sumVector.size()-1] << endl;
				return 999;
			}
		}
		string holder;
		cin >> holder;
	}
	else
	{
		cout << "Could not open file.";
	}
	return 0;
}
