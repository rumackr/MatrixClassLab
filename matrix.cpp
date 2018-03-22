#include "matrix.h"
#include <string>
#include <cmath>

// Parameterized constructor
matrix::matrix(unsigned int rows, unsigned int cols):rows(rows),cols(cols) 
{  
	if (rows < 1 || cols < 1)
	{
		throw matrixException("p-constructor bad arguments");
	}
	this->the_matrix = new double*[rows];
	for (unsigned int i = 0; i < rows; ++i) {
		this->the_matrix[i] = new double[cols];

	}
	this->clear();

//    return this;
}

//TODO Copy constructor
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

//TODO Destructor
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
	if (the_matrix != NULL){
		for (unsigned int i = 0; i < cols; ++i) {
			delete [] this->the_matrix[i];
		}
		delete [] this->the_matrix;
	}

	this->cols = rhs.cols;
	this->rows = rhs.rows;

	double** tempMatrix = new double*[rows];

	for (unsigned int i = 0; i < rows; ++i) {
		tempMatrix[i] = new double[cols];
	}

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
    if(!(this->cols==rhs.rows)) throw matrixException("The number of columns in A must equal the number of rows in B.");
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


//tran operations
matrix matrix::operator~() const
{
	matrix retVal(this->cols,this->rows);

    for (unsigned int m = 1; m <= this->rows ; ++m) {
        for (unsigned int n = 1; n <= this->cols; ++n) {
            retVal.the_matrix[n-1][m-1] = this->the_matrix[m-1][n-1];
        }
    }



	return retVal;
}
	
//TODO clear
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
//get row
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


