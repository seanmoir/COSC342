/* 
   MacOS / Linux shell command for compilation that worked for us:
   c++ Vector.cpp Matrix.cpp matrixMain.cpp -o matrixMain

   Then you can run the resulting executable:
   ./matrixMain
 */


#include "Matrix.h"
#include "Vector.h"

#include <iostream>

int main () {

	Matrix A(3,3);
	Vector v(3);

	A(0,0) = 1;
	A(0,1) = 0;
	A(0,2) = 0;
	A(1,0) = 0;
	A(1,1) = 0.5;
	A(1,2) = -1;
	A(2,0) = 2;
	A(2,1) = 2;
	A(2,2) = 0;

	std::cout << "The Matrix A is:" << std::endl;
	std::cout << A << std::endl;

	v(0) = 1;
	v(1) = 2;
	v(2) = 3;

	std::cout << "The Vector v is:" << std::endl;
	std::cout << v << std::endl;

	Vector u(3);
	u = A*v;
	std::cout << "u = A*v is:" << std::endl;
	std::cout << u << std::endl;


	//Part 5
	u(0) = 1;
	u(1) = -3;
	u(2) = 2;
	v(0) = 3;
	v(1) = 1;
	v(2) = 0;

	std::cout << "2 * u" << std::endl;
	std::cout << 2 * u << std::endl;

	std::cout << "u + v\n" << u + v << std::endl;

	std::cout << "u - v\n" << u - v << std::endl;

	std::cout << "2u - 3v\n" << (2* u) - (3 * v) << std::endl;
	return 0;
}
