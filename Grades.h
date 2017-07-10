
#ifndef GRADES_H
#define GRADES_H

#define DEFAULT_MAX_SIZE 15
#define MAX_COURSES 50
#define MAX_SHEET 250
#include <iostream>

using namespace std;

//this is the grades sheet per object on linked list including an unsigned array, its average, and its size
class Grades
{
public:

	Grades(int);
	Grades();
	bool myConvert(string);
	int getsize() { return this->sizet; };
	int getindex(int i) { return this->_array[i]; };
	float getavg() { return this->average; };
	unsigned int* getGrades() { return this->_array; };
	void setindex(int index, unsigned int value) { this->_array[index] = value; };
	void print();
	void setavg(float i) { average = i; };

private:

	float average;
	int sizet;
	unsigned int* _array;

};



#endif // GRADES_H
