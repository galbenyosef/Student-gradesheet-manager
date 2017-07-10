
#ifndef GRADESHEET_H
#define GRADESHEET_H

#include "Grades.h"
#include <string>
#include <iostream>
#include "cell.h"

//this is the linked list operations class including the head and its size
class GradeSheet
{
public:

	GradeSheet();
	bool printSheet(string name);
	void add(Cell* item);
	void printAll();
	void reAvg(Grades*);
	void MinusMiu(float*, int);
	void MinusMiu(float*, float);
	void printMatrix(float**, int);
	int getMsize() { return headsize; };
	float average(string name);
	float getij(int, int, float* );
	float* makeVector(int);
	float* getXkVector(int);
	float** makeMatrix(int, float*);
	void deleteList(GradeSheet*);
	Cell* getAhead() { return head; };

private:

	Cell* head;
	int headsize;

};


#endif // GRADESHEET_H

