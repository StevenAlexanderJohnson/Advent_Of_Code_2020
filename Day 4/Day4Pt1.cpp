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
		recordVector.push_back(record);
		
		for(auto x: recordVector)
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
				
				switch(intValue)
				{
					case 333:
						passport.birthYear = subs;
						break;
					case 340:
						passport.issueYear = subs;
						break;
					case 336:
						passport.expirationYear = subs;
						break;
					case 323:
						passport.height = subs;
						break;
					case 311:
						passport.hairColor = subs;
						break;
					case 308:
						passport.eyeColor = subs;
						break;
					case 317:
						passport.passportID = subs;
						break;
					case 304:
						passport.countryID = subs;
						break;
					default:
						cout << "Something went wrong: " << subs << endl;
						return 101;
				}
			}
			while(iss);
			if(passport.IsValid())
			{
				validList.push_back(passport);
			}
			passport = Passport();
		}
		cout << "Valid Passports: " << validList.size();
		return 999;
	}
	else
	{
		cout << "Could not open file." << endl;
	}
	return 0;
}
