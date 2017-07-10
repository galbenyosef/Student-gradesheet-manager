
#include "Grades.h"
#include "GradeSheet.h"
#include "cell.h"
#include <string>

GradeSheet::GradeSheet() { head = 0, headsize = 0; }

void GradeSheet::reAvg(Grades* student_sheet)/*recalculate the avg after a update-case */
{
	float sum = 0;
	float newavg;
	unsigned int* temp;
	temp = student_sheet->getGrades();
	for (int i = 0; i < student_sheet->getsize(); i++)
		sum += temp[i];
	newavg = sum / student_sheet->getsize();
	student_sheet->setavg(newavg);
    return;
}

void GradeSheet::add(Cell* item)
{
	Cell* tmpCell = head;
	if (tmpCell) {
		while (tmpCell->getNext() != 0)
		{
			if (tmpCell->getName() == item->getName())
			{
				Grades* overrider = item->getSheet();
				Grades* student_sheet = tmpCell->getSheet();
				for (int k = 0; k < student_sheet->getsize(); k++)
					student_sheet->setindex(k, overrider->getindex(k));
                reAvg(student_sheet);
				cout << "Student: " << item->getName() << " has been UPDATED SUCCESSFULLY" << endl; //basic update
				delete item;
				return;
			}
			tmpCell = tmpCell->getNext();
		}
		//for single and last case
		if (tmpCell->getName() == item->getName())
		{
			Grades* overrider = item->getSheet();
			Grades* student_sheet = tmpCell->getSheet();
			for (int k = 0; k < student_sheet->getsize(); k++)
				student_sheet->setindex(k, overrider->getindex(k));
			cout << "Student: " << item->getName() << " has been UPDATED SUCCESSFULLY" << endl; //single and last update
			delete item;
		}
		else {
			tmpCell->setNext(item);
			headsize++;
			cout << "Student: " << item->getName() << " has been ADDED SUCCESSFULLY" << endl; //basic add
		}
	}
	else {
		head = item;
		headsize++;
		cout << "Student: " << item->getName() << " has been INITIALIZED SUCCESSFULLY" << endl; //single and last add
	}
}

bool GradeSheet::printSheet(string name) // simple find and print by given string
{
	Grades* temp;
	Cell* tmpCell = head;
	if (tmpCell) {

		while (tmpCell->getNext() != 0)
		{
			if (tmpCell->getName() == name)
			{
				temp = tmpCell->getSheet();
				cout << name << " -> ";
				temp->print();
				return 1;
			}
			tmpCell = tmpCell->getNext();
		}
		if (tmpCell->getName() == name)
		{
			temp = tmpCell->getSheet();
			cout << name << " -> ";
			temp->print();
			return 1;
		}
	}
	return 0;
}

void GradeSheet::printAll() /*print all students names and averages by get functions*/
{
	Grades* temp;
	Cell* tmpCell = head;
	if (tmpCell) {
		while (tmpCell->getNext() != 0)
		{
			temp = tmpCell->getSheet();
			cout << tmpCell->getName() << ", " << ((float)((int)(100*temp->getavg()))/100) << endl;
			tmpCell = tmpCell->getNext();
		}
		if (tmpCell)
		{
			temp = tmpCell->getSheet();
			cout << tmpCell->getName() << ", " << ((float)((int)(100*temp->getavg()))/100) << endl;
			tmpCell = tmpCell->getNext();
		}
	}
}

float GradeSheet::average(string name)// simple find and return
{
	Grades* temp;
	Cell* tmpCell = head;
	if (tmpCell) {

		while (tmpCell->getNext() != 0)
		{
			if (tmpCell->getName() == name)
			{
				temp = tmpCell->getSheet();
				return temp->getavg();
			}
			tmpCell = tmpCell->getNext();
		}
		if (tmpCell->getName() == name)
		{
			temp = tmpCell->getSheet();
			return temp->getavg();
		}
	}
	return -1;
}

float* GradeSheet::makeVector(int sizet) //this is the Expectancy vector creator function
{
	float* new_vector = new float[sizet];
	float temp_sum = 0;
	Grades* temp;
	for (int i = 0; i<sizet; i++)
	{
		Cell* tmpCell = head;
		if (tmpCell) {
			//basic case
			while (tmpCell->getNext() != 0)
			{
				temp = tmpCell->getSheet();
				temp_sum += temp->getindex(i);
				tmpCell = tmpCell->getNext();
			}
			//single and last case;
			if (tmpCell)
			{
				temp = tmpCell->getSheet();
				temp_sum += temp->getindex(i);
			}
			new_vector[i] = temp_sum / headsize;
		}
		temp_sum = 0;
	}
	return new_vector;
}


void GradeSheet::printMatrix(float** mymatrix, int sizet)
{
	for (int i = 0; i < sizet; i++)
	{
		cout << endl;
		for (int j = 0; j < sizet; j++)
		{
			cout << ((float)((int)(100*mymatrix[i][j] ))/100)<< " ";
		}
	}
	cout << endl;
}

float** GradeSheet::makeMatrix(int sizet, float* MiuVector)
{
	float** MyMatrix = new float*[sizet]; //basic allocation of 2d array
	for (int i = 0; i < sizet; i++)
		MyMatrix[i] = new float[sizet];
	for (int i = 0; i < sizet; i++)
		for (int j = 0; j < sizet; j++) // sets the matrix's cells by the next function called 'getij'
		{
			MyMatrix[i][j] = getij(i, j, MiuVector);
		}
	return MyMatrix;
}

float GradeSheet::getij(int i, int j, float* MiuVector) // this is the main calculation function by the given formula
{
	float final_result = 0; // this will be the final score without dividing by M
	float* Xi = getXkVector(i); // get all xi(1->M) and put them on vector
	float* Xj = getXkVector(j); // get all xj(1->M) and put them on vector
	MinusMiu(Xi, MiuVector[i]); // minus X(i,j) by miu vector by its index
	MinusMiu(Xj, MiuVector[j]);
	for (int s = 0; s < headsize; s++) //Inner Multiplication
		final_result += (Xi[s] * Xj[s]);
	delete Xi;
	delete Xj;
	if (headsize==1)//finally
		return final_result/headsize;
	return final_result / (headsize - 1);
}

/*void GradeSheet::MinusMiu(float* Vector, int miu) // gets a vector and reduces from its all values an integer
{
	for (int i = 0; i < headsize; i++)
		Vector[i] -= miu;
	return;
}*/

void GradeSheet::MinusMiu(float* Vector, float miu)
{
	for (int i = 0; i < headsize; i++)
		Vector[i] -= miu;
	return;
}


float* GradeSheet::getXkVector(int k) // this is how I build the X(i,j) vectors for later use on formula
{
	Grades* temp;
	Cell* tmpCell = head;
	float* tempArray = new float[headsize];
	int i = 0;
	if (tmpCell) {
		//basic case
		while (i < headsize)
		{
			if (tmpCell) {
				//basic case
				while (tmpCell->getNext() != 0)
				{
					temp = tmpCell->getSheet();
					tempArray[i] = (float)temp->getindex(k);
					i++;
					tmpCell = tmpCell->getNext();
				}
				//single and last case
				if (tmpCell)
				{
					temp = tmpCell->getSheet();
					tempArray[i] = (float)temp->getindex(k);
					break;
				}
			}
		}
	}
	return tempArray;
}

void GradeSheet::deleteList(GradeSheet* head_ref)
{
   GradeSheet* current = head_ref;
   Cell* tempi=current->head;
   Cell* next;
   Grades* temp;
   while (tempi != NULL)
   {
       temp=tempi->getSheet();
       delete(temp->getGrades());
       next = tempi->getNext();
       delete(tempi);
	   delete(temp);
       tempi = next;
   }
   head_ref = NULL;
}
