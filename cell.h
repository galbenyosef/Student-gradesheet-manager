
#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

#include "Grades.h"

//This class represents the linked list objects and constructors
class Cell {

public:

	Cell(string name, Grades* marks)
	{
		m_name = name;
		m_next = 0;
		m_sheet = marks;
	}

	Cell(string name)
	{
		m_name = name;
		m_next = 0;
		m_sheet = 0;
	}

	string getName() { return this->m_name; }
	Cell* getNext() { return this->m_next; }
	void setNext(Cell* item) { m_next = item; }
	Grades* getSheet() { return this->m_sheet; }

private:

	string m_name;
	Grades* m_sheet;
    Cell* m_next;
};


#endif // CELL_H_INCLUDED
