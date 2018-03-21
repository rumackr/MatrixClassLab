#include "matrix.h"
#include <iostream>
 
using namespace std;

int main(void)
{
	// test our matrix
	
	matrix m1(3,3);
	
	cout << "m1 - should be all zeros" << endl;
	cout << m1 << endl;
	
	matrix m2 = matrix::identity(3);

	cout << "m2 - should be 3 x 3 identity matrix" << endl;
	cout << m2 << endl;

	matrix m3 = m1 + m2;

	cout << "m3 - should be 3 x 3 identity matrix" << endl;
	cout << m3 << endl;


	try
	{
		matrix m4(0,0);	// should throw
		cout << "m4 - exception not thrown (but should have)" << endl;
	}
	catch (matrixException me)
	{
		cout << "m4 - exception expected and thrown" << endl;
	}

    matrix m5(2,3);

    m5[0][0]=1;    m5[0][1]=2;     m5[0][2]=3;
    m5[1][0]=4;    m5[1][1]=5;     m5[1][2]=6;
    cout << m5;

    matrix m6(3,2);
    m6[0][0]=7;    m6[0][1]=8;
    m6[1][0]=9;    m6[1][1]=10;
    m6[2][0]=11;   m6[2][1]=12;
    cout << "  -------- m5 ---------"<<endl;
    cout << m5 <<endl;
    cout << "  -------- m6 ---------"<<endl;
    cout << m6 <<endl;
    cout << "  -------- m5 * m6 ---------"<<endl;
    cout << m5*m6;
    cout << "  -------- m5 + m5 + m5 ---------"<<endl;
    cout << m5+ m5 + m5;
    cout << "  -------- m5*2 ---------"<<endl;
    cout << m5*2;
    cout << "  -------- m1=~m5 ---------"<<endl;
    m1 =(~m5);
    cout << m1;
    cout << "  -------- m1+m6 ---------"<<endl;
    cout << m1+m6;
    cout << "  -------- 0.5 * m5 ---------"<<endl;
    cout << 0.5 * m5;

    return 1;
}		
