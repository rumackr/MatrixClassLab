/**
 * @author Reid Rumack
 * @file matrix.cpp
 * @date 3/21/2018
 * @lab lab 2
 *
 *
 * Defines a matrix class and provides overloaded operators
 * to allow for you do matrix math. indexes from 0
 *
 */

#include "matrix.h"
#include <string>
#include <cmath>
#define
// Parameterized constructor
matrix::matrix(unsigned int rows, unsigned int cols):rows(rows),cols(cols) 
{  
	if (rows < 1 || cols < 1)
	{
		throw matrixException("p-constructor bad arguments");
	}
	//creates new matrix
	this->the_matrix = new double*[rows];
	for (unsigned int i = 0; i < rows; ++i) {
		this->the_matrix[i] = new double[cols];

	}
	//sets values to 0
	this->clear();

}

//Copy constructor
matrix::matrix(const matrix& from):rows(from.rows),cols(from.cols)
{
	//create new matrix
	this->the_matrix = new double*[rows];
	for (unsigned int i = 0; i < rows; ++i) {
		this->the_matrix[i] = new double[cols];
	}

	//copy matrix;
	for (unsigned int m = 0; m < rows; ++m) {
		for (unsigned int n = 0; n < cols; ++n) {
			this->the_matrix[m][n] = from.the_matrix[m][n];
		}
	}


}

//Destructor
matrix::~matrix()
{
		for (unsigned int i = 0; i < rows; ++i) {
				delete [] this->the_matrix[i];
		}
		delete[] this->the_matrix;
}

// Assignment operator
matrix& matrix::operator=(const matrix& rhs)
{
	if (rhs.rows < 1 || rhs.cols < 1)
	{
		throw matrixException("invalid matrix size");
	}
	// deletes the values in this matrix
	if (the_matrix != NULL){
		for (unsigned int i = 0; i < cols; ++i) {
			delete [] this->the_matrix[i];
		}
		delete [] this->the_matrix;
	}

	this->cols = rhs.cols;
	this->rows = rhs.rows;
	//inits new matrix
	double** tempMatrix = new double*[rows];
	for (unsigned int i = 0; i < rows; ++i) {
		tempMatrix[i] = new double[cols];
	}
	//copys values
	for (unsigned int i = 0; i < rows; ++i) {
		for (unsigned int j = 0; j < cols; ++j) {
			tempMatrix[i][j] = rhs.the_matrix[i][j];
		}
	}

	this->the_matrix = tempMatrix;

	return *this;
}

// Named constructor (static)
matrix matrix::identity(unsigned int size)
{
	if(size == 0) throw matrixException("size can not be zero");

	matrix idMatrix = matrix(size,size);
	for (unsigned int i = 0; i < size; ++i) {
		idMatrix.the_matrix[i][i] = 1;
	}
    return idMatrix;
}


// Binary operations
matrix matrix::operator+(const matrix& rhs) const
{
    if(!((this->rows==rhs.rows)&&(this->cols==rhs.cols))) throw matrixException("Matrices are not of the same size ");
	matrix retVal(rows,cols);
    for (unsigned int m = 0; m < this->rows ; ++m) {
        for (unsigned int n = 0; n < this->cols; ++n) {
            retVal.the_matrix[m][n]= this->the_matrix[m][n]+rhs.the_matrix[m][n];
        }
    }

	return retVal;
}

//multiplication
matrix matrix::operator*(const matrix& rhs) const
{
    if(this->cols!=rhs.rows)
        throw matrixException("The number of columns in A must equal the number of rows in B.");

	matrix retVal(this->rows, rhs.cols);
    for (unsigned int m = 0; m < this->rows ; m++) {
        for (unsigned int n = 0; n < rhs.cols; n++) {
            for (unsigned int i = 0; i < rhs.rows; i++) {
                retVal[m][n]+= this->the_matrix[m][i]*rhs[i][n];
            }
        }

    }
	return retVal;
}
// scales matrix
matrix matrix::operator*(const double scale) const
{
    matrix retVal(*this);

    for (unsigned int m = 0; m < this->rows ; ++m) {
        for (unsigned int n = 0; n < this->cols; ++n) {
            retVal.the_matrix[m][n]*=scale;
        }
    }
	return retVal;
}


///Transpose operation
matrix matrix::operator~() const
{
	matrix retVal(this->cols,this->rows);

    for (unsigned int m = 0; m < this->rows ; ++m) {
        for (unsigned int n = 0; n < this->cols; ++n) {
            retVal.the_matrix[n][m] = this->the_matrix[m][n];
        }
    }



	return retVal;
}
	
//clear- sets all values to 0
void matrix::clear()
{
	if(rows < 1 || cols < 1) throw matrixException("[from clear()] matrix not initialized");
	for (unsigned int m = 0; m <rows ; ++m) {
		for (unsigned int n = 0; n < cols; ++n) {
			this->the_matrix[m][n] = 0;

		}
	}
	return;
}
//get ro
double* matrix::operator[](unsigned int row)
{
	if(((row <  0)&&(row > this->rows))) {
		throw matrixException("Row index is out of bounds");
	}
	return this->the_matrix[row];
}

double* matrix::operator[](unsigned int row) const
{
	if(((row < 0)&&(row > this->rows))) {
		throw matrixException("Row index is out of bounds");
	}
	return this->the_matrix[row];
}

///out stream definition for the matrix class
std::ostream& matrix::out(std::ostream& os) const
{
		for (unsigned int m = 0; m < this->rows; ++m) {
			(m==0)? (os<< "[[") : (os<< " [");

			for (unsigned int n = 0; n < this->cols; ++n) {
				if (n != this->cols-1) {
					os << " " << this->the_matrix[m][n] << ",";

				} else {
					os << " " << this->the_matrix[m][n];
				}
			}
			if(m == this->rows - 1) {
				os << "]]" << std::endl;

			} else{
				os << "]" << std::endl;
			}
		}

	return os;	
}



// Global insertion and operator
std::ostream& operator<<(std::ostream& os, const matrix& rhs)
{
	rhs.out(os);
	return os;
}

// Global scalar multiplication
matrix operator*(const double scale, const matrix& rhs)
{
	matrix retval(rhs);
	return retval*scale;
}


