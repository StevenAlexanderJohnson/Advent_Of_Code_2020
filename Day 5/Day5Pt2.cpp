#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Partition the list for the Quick Sort.
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

// Quick sorting algorithm.
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
	// Crating the file reader.
	ifstream inputFile("Input.txt");
	
	// If the file is opened correctly run the code.
	if(inputFile.is_open())
	{
		// Vector to hold all of the boarding passes.
		vector<string> boardingPasses;
		// vector to hold all the seat IDs.
		vector<int> seatIDs;
		// Variable to hold the line value.
		string line;
		
		// While there are lines to read in the file read them.
		while(getline(inputFile, line))
		{
			// Add all the boarding passes to the vector.
			boardingPasses.push_back(line);
		}
		
		// Finding the boarding all the boarding passes the same way as in Pt 1 but this time saving each
		// in the seatIDs vector.
		int lowRange = 0;
		int highRange = 127;
		int leftRange = 0;
		int rightRange = 7;
		for(auto pass: boardingPasses)
		{
			for(char letter: pass)
			{
				if(letter == 'F')
				{
					highRange = int((lowRange + highRange)/2);
				}
				else if(letter == 'B')
				{
					lowRange = int((lowRange + highRange)/2)+1;
				}
				else if(letter == 'L')
				{
					rightRange = int((leftRange + rightRange)/2);
				}
				else if(letter == 'R')
				{
					leftRange = int((leftRange + rightRange)/2)+1;
				}
			}
			if(highRange != lowRange || leftRange != rightRange)
			{
				cout << "Error in calculation." << endl;
				break;
			}
			
			// Add the found seat ID to the vector.
			seatIDs.push_back((highRange * 8) + rightRange);
			
			// Reset all the ranges.
			highRange = 127;
			lowRange = 0;
			leftRange = 0;
			rightRange = 7;
		}
		
		// QuickSort all of the seat ids so you can find the gap.
		QuickSort(seatIDs, 0, seatIDs.size());
		
		// For every seat ID in the array, look for one that does not have a seat ID that is one less than
		// the next.
		for(int i = 1; i < seatIDs.size()-1; i++)
		{
			// If the seat is found return the next seat.
			if(seatIDs[i+1] != (seatIDs[i] + 1))
			{
				cout << "Your seat is: " << seatIDs[i] + 1 << endl;
			}
		}
		return 999;
	}
	else
	{
		cout << "Could not open file." << endl;
		return -1;
	}
	
	return 0;
}
