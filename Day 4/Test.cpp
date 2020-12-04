#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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
	ifstream inputFile("TestInput.txt");
	
	// If it opened correctly run the code otherwise tell the user.
	if(inputFile.is_open())
	{
		// Creating passport record and list of valid passports.
		Passport passport;
		vector<Passport> validList = vector<Passport>();
		
		// Reading the file line by line.
		string line;
		string test;
		vector<string> testVector;
		while(getline(inputFile, line))
		{
			if(line.empty())
			{
				testVector.push_back(test);
				test.clear();
				continue;
			}
			test = test + line + " ";
		}
		testVector.push_back(test);
		
		for(auto x: testVector)
		{
			istringstream iss(x);
			do
			{
				char subs[3];
				
				iss >> subs;
				int intValue = 0;
				for(int i = 0; i < 3; i++)
				{
					intValue += int(subs[i]);
				}
				
				string stringValue = string(subs);
				switch(intValue)
				{
					case 333:
						passport.birthYear = stringValue.substr(4);
						break;
					case 340:
						passport.issueYear = stringValue.substr(4);
						break;
					case 336:
						passport.expirationYear = stringValue.substr(4);
						break;
					case 323:
						passport.height = stringValue.substr(4);
						break;
					case 311:
						passport.hairColor = stringValue.substr(4);
						break;
					case 308:
						passport.eyeColor = stringValue.substr(4);
						break;
					case 317:
						passport.passportID = stringValue.substr(4);
						break;
					case 304:
						passport.countryID = stringValue.substr(4);
						break;
					default:
						cout << "Something went wrong: " << subs << endl;
						return 101;
				}
			}
			while(iss);
			if(passport.IsValid())
			{
				passport.PrintPassport();
				validList.push_back(passport);
			}
			passport = Passport();
		}
		return validList.size();
	}
	else
	{
		cout << "Could not open file." << endl;
	}
	return 0;
}
