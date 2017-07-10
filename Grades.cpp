#include "Grades.h"
#include <sstream>


Grades::Grades()
{
	int i = 0;
	sizet = DEFAULT_MAX_SIZE;
	_array = new unsigned int[DEFAULT_MAX_SIZE];
	while (i<DEFAULT_MAX_SIZE) {
		_array[i] = 0;
		i++;
	}
	average = 0;
}

Grades::Grades(int n)
{
	int i = 0;
	_array = new unsigned int[n];
	sizet = n;
	while (i<n) {
		_array[i] = 0;
		i++;
	}
	average = 0;
}


bool Grades::myConvert(string n) //converts input string to unsigned int array by delimeter, second part sets the relevant array (means input is valid!);
{
	unsigned int* sheetArray = new unsigned int[MAX_COURSES];
	unsigned int mark = 0;
	string token;
	string delimiter = ",";
	size_t pos = 0;
	int i = 0;
	//take characters untill delimeter is appearing, then convert from string to int, cut last token include delimeter and restart untill string is over.
	while ((pos = n.find(delimiter)) != string::npos && i<MAX_COURSES) {

		token = n.substr(0, pos);
		stringstream convert(n);
		if (!(convert >> mark) || mark > 100 || mark < 0)
		{
			delete[] sheetArray;
			return 0;
		}
		sheetArray[i] = mark; // set mark if passed all tests
		i++;
		n.erase(0, pos + delimiter.length());

	}
	//for single and last case;
	stringstream convert(n);
	if (!(convert >> mark) || mark > 100 || mark < 0 || i != sizet-1 )
	{
		delete[] sheetArray;
		cin.ignore();
		return 0;
	}
	sheetArray[i] = mark;
	//PASSED ALL TESTS, NOW SET THE RELEVANT ARRAY AND CALCULATE ITS AVERAGE;
	for (int j=0;j<sizet;j++)
	{
		setindex(j,sheetArray[j]);
		average+=getindex(j);
	}
	average=average/sizet;
	delete[] sheetArray;
	cin.ignore();
	return 1;
}



void Grades::print()
{
	unsigned int* printarray = this->getGrades();
	cout << "[ ";
	for (int i = 0; i < this->sizet; i++)
		cout << printarray[i] << " ";
	cout << "]";

}
