#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Creating class to hold passport information.
class Passport {
	public:
		string birthYear;
		string issueYear;
		string expirationYear;
		string height;
		string hairColor;
		string eyeColor;
		string passportID;
		string countryID;
		
		vector<string> possibleEyeColors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
		
		
		// Method to check if passport is valid.
		bool IsValid()
		{
			if(!birthYear.empty() && !issueYear.empty() &&
			   !expirationYear.empty() && !height.empty() &&
			   !hairColor.empty() && !eyeColor.empty() &&
			   !passportID.empty())
			{
				return true;
			}
		}
		
		// Method to check if input value is a valid eye color.
		bool IsValidEyeColor(string input)
		{
			for(string color: this->possibleEyeColors)
			{
				if(color == input)
				{
					return true;
				}
			}
			return false;
		}
		
		// Method to print out the passport.
		void PrintPassport()
		{
			cout << "Birth Year: " << birthYear << endl;
			cout << "Issue Year: " << issueYear << endl;
			cout << "Expiration Year: " << expirationYear << endl;
			cout << "Height: " << height << endl;
			cout << "Hair Color: " << hairColor << endl;
			cout << "Eye Color: " << eyeColor << endl;
			cout << "Passport ID: " << passportID << endl;
			cout << "Country ID: " << countryID << endl;
			cout << "Valid: " << this->IsValid() << endl << endl;
		}
		
		// Contstructor to set the object empty.
		Passport()
		{
			birthYear.clear();
			issueYear.clear();
			expirationYear.clear();
			height.clear();
			hairColor.clear();
			eyeColor.clear();
			passportID.clear();
			countryID.clear();
		}
};

int main()
{
	// Creating input file stream.
	ifstream inputFile("Input.txt");
	
	// If it opened correctly run the code otherwise tell the user.
	if(inputFile.is_open())
	{
		// Creating passport record and list of valid passports.
		Passport passport;
		vector<Passport> validList = vector<Passport>();
		
		// Reading the file line by line.
		string line;
		string record;
		vector<string> recordVector;
		// While there are lines to read add them to the record string.
		while(getline(inputFile, line))
		{
			if(line.empty())
			{
				recordVector.push_back(record);
				record.clear();
				continue;
			}
			record = record + line + " ";
		}
		// Add record to record vector.
		recordVector.push_back(record);
		
		// Loop through all records in the list of records.
		for(auto x: recordVector)
		{
			// Put the record in a string stream.
			istringstream iss(x);
			
			// While there are still words in the string stream run the code.
			do
			{
				char subs[3];
				
				iss >> subs;
				
				// Getting int representation of word.
				int intValue = 0;
				for(int i = 0; i < 3; i++)
				{
					intValue += int(subs[i]);
				}
				
				// Getting string value of word without header.
				string stringValue = string(subs).substr(4);
				
				// Value to hold numbers during calculation.
				int numberValue;
				// Value to hold the unit in height calculation.
				string unit;
				
				// Using int representation of the words to choose correct operation.
				switch(intValue)
				{
					// Birth Year
					case 333:
						if(stringValue.size() == 4 && stoi(stringValue) >= 1920 && stoi(stringValue) <= 2002)
						{
							passport.birthYear = stringValue;
						}
						break;
					
					// Issue Year	
					case 340:
						if(stringValue.size() == 4 && stoi(stringValue) >= 2010 && stoi(stringValue) <= 2020)
						{
							passport.issueYear = stringValue;
						}
						break;
					
					// Expiration Year	
					case 336:
						if(stringValue.size() == 4 && stoi(stringValue) >= 2020 && stoi(stringValue) <= 2030)
						{
							passport.expirationYear = stringValue;
						}
						break;
					
					// Height	
					case 323:
						// Checking if there is a unit.
						unit = stringValue.substr(stringValue.size()-2);
						// If there is a unit get the number value, else break;
						if(unit == "cm" || unit == "in")
						{
							numberValue = stoi(stringValue.substr(0, stringValue.size()-2));
						}
						else
						{
							break;
						}
						// Checking number parameters using ASCII values for the range.
						if(unit == "cm" && numberValue >= 150 && numberValue <= 193)
						{
							passport.height = stringValue;
						}
						else if(unit == "in" && numberValue >= 59 && numberValue <= 76)
						{
							passport.height = stringValue;
						}
						break;
					
					// Hair Color	
					case 311:
						// If the rgb value starts in a # and has characters following, check
						// to make sure the following characters are all digits.
						if(stringValue.substr(0,1) == "#" && stringValue.substr(1).size() == 6)
						{
							// Reset numberValue.
							numberValue = 0;
							// For every value in the string check if it falls under the correct
							// ASCII range.
							for(char letter: stringValue.substr(1))
							{
								if(int(letter) >= 48 && int(letter) <= 57)
								{
									numberValue++;
								}
								else if(int(letter) >= 97 && int(letter) <= 102)
								{
									numberValue++;
								}
							}
							// If all the following characters are numeric add it to the record.
							if(numberValue == 6)
							{
								passport.hairColor = stringValue;
							}
						}
						break;
					
					// Eye Color	
					case 308:
						if(stringValue.size() == 3 && passport.IsValidEyeColor(stringValue))
						{
							passport.eyeColor = stringValue;
						}
						break;
					
					// Passport ID	
					case 317:
						for(int i = 0; i < stringValue.size(); i++)
						{
							if(!isdigit(stringValue[i]))
							{
								break;
							}
						}
						if(stringValue.size() == 9)
						{
							passport.passportID = stringValue;
						}
						break;
					
					// Country ID	
					case 304:
						passport.countryID = subs;
						break;
					
					// Incase there was an input that didn't fall into the correct
					// catagory.	
					default:
						cout << "Something went wrong: " << subs << endl;
						return 101;
				}
			}
			while(iss);
			
			// If the passport is valid add it to the list.
			if(passport.IsValid())
			{
				validList.push_back(passport);
			}
			// Reset the passport.
			passport = Passport();
		}
		
		// Closing input file.
		inputFile.close();
		
		// Print how many passports are in the valid passport vector.
		cout << "Valid Passports: " << validList.size();
		return 999;
	}
	else
	{
		cout << "Could not open file." << endl;
	}
	return 0;
}
