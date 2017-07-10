#include "GradeSheet.h"
#include "cell.h"
#include <stdlib.h>

using namespace std;

int main(int argc, const char* argv[])
{
	if (argc == 3){
		int sizet = atoi(argv[1]);
		int max_size = atoi(argv[2]);
		if (sizet<MAX_COURSES/*50 - AS MAX*/ && sizet > 0 && max_size>0 && max_size<MAX_SHEET)
		{
			GradeSheet* cList = new GradeSheet();
			Cell* pCell;
			Grades* pGrades;
			string name;
			string input;
			float temp2;
			float* myvector;
			float** mymatrix;
			int operation;

			while (true)
			{
				int temp=cList->getMsize(); //size of the list (student number)
				cout << "Commands List:\n" << "Please type your operation:\n";
				cout << "1. Set student gradesheet\n";
				cout << "2. Get student gradesheet\n";
				cout << "3. Get student average\n";
				cout << "4. Get all students averages\n";
				cout << "5. Get all courses averages\n";
				cout << "6. Print Covariance matrix\n";
				cout << "0. Quit\n";
				cin >> operation;
				if (cin.fail()) { operation = -1; }
				switch (operation) {

				case (1) :
					cout << string(50, '\n');
					if (temp == max_size) //limit check
					{
						cerr << "You have reached " << cList->getMsize() << " students which is the maximum" << endl;
						break;
					}
					cout << "Please type student name: ";
					cin >> name;
					if (name.length() < 11 && name.compare("cov")!=0 && name.compare("mean")!=0 )//check for limited size and used words
						{
						cout << "Please type (" << name << "'s) (" << sizet << ") grades seperated by comma (','): ";
						cin >> input;
						pGrades = new Grades(sizet);
						if(pGrades->myConvert(input))
						{
							pCell = new Cell(name, pGrades);
							cList->add(pCell);
							break;
						}
					}
					cerr << "ERROR MSG: WRONG INPUT (Could be size > 10 or used words ('mean','cov')" << endl;
					break;
				case (2) :
					cout << string(50, '\n');
					cout << "Please type student name: ";
					cin >> name;
					if(!cList->printSheet(name))
						cerr << "ERROR MSG: NAME NOT FOUND" << endl;
					break;
				case (3) :
					cout << string(50, '\n');
					cout << "Please type student name: " << endl;
					cin >> name;
					temp2 = ((float)((int)(100*cList->average(name)))/100);
					if (temp2 == -1)
					{
						cerr << name << "average uninitialized\n" << endl;
						break;
					}
					//get an float, multiply by 100 and cast to int to receive its only 2 digits after point, finally make it float to get back the point and divide by 100.
					cout << name << "'s average: " << temp2 << endl;
					break;
				case (4) :
					cout << string(50, '\n');
					cList->printAll();
					break;
				case (5) :
					cout << string(50, '\n');
					myvector = cList->makeVector(sizet);
					cout << "mean = [ ";
					for (int i = 0; i< sizet; i++)
					{
						cout <<((float)((int)(100*myvector[i]))/100) << " ";
					}
					cout << "]" << endl;
					delete[] myvector;
					break;
				case (6) :
					cout << string(50, '\n');
					myvector = cList->makeVector(sizet);
					mymatrix = cList->makeMatrix(sizet, myvector);
					cout << "cov = [ " << endl;
					cList->printMatrix(mymatrix,sizet);
					cout << endl << "]" << endl;
					delete[] myvector;
					delete[] mymatrix;
					break;
				case (0) :
					cList->deleteList(cList);
					delete(cList);
					cout << "\nBye Bye...";
					//release all list;
					//finish
					return false;
				default :
					cerr << "\nInvalid input\n";
					cin.clear();
					cin.ignore();
					break;
				}
			}
		}
		cerr << "\nInvalid arguments value;\n";
		exit(0);
	}
	cerr << "\nInvalid arguments size; please enter two.\n";
	exit(0);
}
