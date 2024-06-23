// Kelsey Hodge
// COP2000.0T1
// Project 8 - This program reads one file containing a list of names, and another file containing a 
// list of birth years. The names and birth years are stored in two arrays which are ordered such that 
// at each index, the name matches the birth year as listed in the two files. Next the program sorts 
// the names array into alphabetical order and displays the list of names followed by the name's 
// corresponding birth year. Next the user is prompted to input a birth year from 1995 through 
// 2005 and if the input is valid, all names with a birth year matching the user input are displayed on the screen.

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
int const NUM_ITEMS = 30;

class Birthdays
{

private:
	// Private member variables
	ifstream inputFile1;
	ifstream inputFile2;

	int birthYears[NUM_ITEMS] = {}; // Int array to hold the birth years, initialized to all zeros.
	string names[NUM_ITEMS];		// String array to hold the names.

	int birthYear = 1995;
	string name = "";

	// Private member functions
	void openFiles();
	void validateFiles();
	void readFiles();
	void closeFiles();
	void sortFiles(string[NUM_ITEMS], int[NUM_ITEMS]);
	void displaySortedData(string[NUM_ITEMS], int[NUM_ITEMS]);
	void getYear();
	void displayNames(string[NUM_ITEMS], int[NUM_ITEMS]);

// Public member Functions
public:
	void driver();
};

// Opens the input files.
void Birthdays::openFiles()
{
	inputFile1.open("Names.txt");
	inputFile2.open("BirthYear.txt");
}

// Validates the input files.
void Birthdays::validateFiles()
{
	if (!inputFile1 || !inputFile2)
	{
		cout << "File could not be opened.";
		return;
	}
}

// Reads data from file and store names and birth years into two different arrays.
void Birthdays::readFiles()
{
	for (int i = 0; i < NUM_ITEMS; i++)
	{
		inputFile1 >> names[i];
	}
	for (int j = 0; j < NUM_ITEMS; j++)
	{
		inputFile2 >> birthYears[j];
	}
}

// Closes input files.
void Birthdays::closeFiles()
{
	inputFile1.close();
	inputFile2.close();
}

// Sorts names and birth years.
void Birthdays::sortFiles(string n[NUM_ITEMS], int b[NUM_ITEMS])
{
	bool outOfOrder;
	string name2Swap;
	int birthYear2Swap;
	do {
		outOfOrder = false;
		for (int i = 0; i < (NUM_ITEMS - 1); i++)
		{
			if (n[i] > n[i + 1])
			{
				outOfOrder = true;
				name2Swap = n[i];
				n[i] = n[i + 1];
				n[i + 1] = name2Swap;

				birthYear2Swap = b[i];
				b[i] = b[i + 1];
				b[i + 1] = birthYear2Swap;
			}
		}
	}
	while (outOfOrder);
}

// Outputs the sorted names and their corresponding birth year.
void Birthdays::displaySortedData(string n[NUM_ITEMS], int b[NUM_ITEMS])
{
	cout << "Alphabetical Roster of Names\n\n";
	for (int i = 0; i < NUM_ITEMS; i++)
	{
		cout << setw(9) << left << n[i] << setw(6) << right << birthYears[i] << endl;
	}
	cout << "\n\n";
}

// Prompts user to enter a birth year until they enter a valid year.
void Birthdays::getYear()
{
	cout << "Names by Birth Year\n\n";
	cout << "Please enter the birth year: ";
	cin >> birthYear;
	cout << endl;
	while (!cin || birthYear < 1995 || birthYear > 2005)
	{
		cin.clear();
		fseek(stdin, 0, SEEK_END);
		cout << "Invalid birth year entered, try again: ";
		cin >> birthYear;
	}
}

// Displays names with the birth year that matches the user input.
void Birthdays::displayNames(string n[NUM_ITEMS], int b[NUM_ITEMS])
{
	bool found = false;
	for (int i = 0; !found; i++) 
	{
		if (b[i] == birthYear)
		{
			cout << "For the birth year of " << b[i] << ":\n\n";
			found = true;
		}
		else if (b[i] != birthYear && i > NUM_ITEMS)
		{
			cout << "\nNo names with the birth year " << birthYear << "." << endl;
			cout << "\nEnd of results.\n\n\n\n";
			exit(1);
		}
	}
	for (int i = 0; i < NUM_ITEMS; i++)
	{
		while (b[i] == birthYear && i < NUM_ITEMS)
		{
			cout << n[i] << endl;
			i++; // move to the next element in the array
		}
	}
	cout << "\n\nEnd of results\n\n\n\n";
}

// Driver calls private member functions.
void Birthdays::driver()
{
	openFiles();
	validateFiles();
	readFiles();
	sortFiles(names, birthYears);
	displaySortedData(names, birthYears);
	getYear();
	displayNames(names, birthYears);
}

int main()
{
	Birthdays findTheBirthdays;
	findTheBirthdays.driver();
	system("pause");
	return 0;
}