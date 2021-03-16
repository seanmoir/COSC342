
// Simple, portable image I/O libraries
#include "Image.h"

// Standard I/O
#include <iostream>

// Will be needed for trigonometric functions
#include <cmath>

int main(int argc, char *argv[])
{

	// Expecting two arguments
	if (argc != 3)
	{
		std::cout << "Usage: ImageTransforms <input image> <output image>" << std::endl;
		exit(-1);
	}

	Image inputImage;

	inputImage.read(argv[1]);

	Image outputImage(inputImage.width(), inputImage.height());

	Vector v(3);
	v(2) = 1;

	Matrix R(3,3);
	/*T(0,0) = 1; T(0,1) =0; T(0,2) = -50;
	T(1,0) = 0; T(1,1) =1; T(1,2) = 20;
	T(2,0) = 0; T(2,1) =0; T(2,2) = 1;*/
	R(0,0) = cos((M_PI * 30)/180); R(0,1) = - sin((M_PI * 30)/180); R(0,2) = 0;
	R(1,0) = sin((M_PI * 30)/180); R(1,1) = cos((M_PI* 30)/180); R(1,2) = 0;
	R(2,0) = 0; R(2,1) = 0; R(2,2) = 1;

	Matrix Rinv(3, 3);
	Rinv(0,0) = cos((M_PI * 30)/180); Rinv(0,1) = sin((M_PI * 30)/180); Rinv(0,2) = 0;
	Rinv(1,0) = - sin((M_PI * 30)/180); Rinv(1,1) = cos((M_PI* 30)/180); Rinv(1,2) = 0;
	Rinv(2,0) = 0; Rinv(2,1) = 0; Rinv(2,2) = 1;

	Matrix T2(3, 3);
	T2(0,0) = 1; T2(0,1) = 0; T2(0,2) = inputImage.width() / 2;
	T2(1,0) = 0; T2(1,1) = 1; T2(1,2) = inputImage.height() / 2;
	T2(2,0) = 0; T2(2,1) = 0; T2(2,2) = 1;

	Matrix T1(3, 3);
	T1(0,0) = 1; T1(0,1) = 0; T1(0,2) = -(inputImage.width() / 2);
	T1(1,0) = 0; T1(1,1) = 1; T1(1,2) = -(inputImage.height() / 2);
	T1(2,0) = 0; T1(2,1) = 0; T1(2,2) = 1;

	Matrix S(3, 3);
	S(0,0) = 0.5; S(0,1) = 0; S(0,2) = 0;
	S(1,0) = 0; S(1,1) = 0.5; S(1,2) = 0;
	S(2,0) = 0; S(2,1) = 0; S(2,2) = 0.5;	

	try
	{
			for (v(1) = 0; v(1) < inputImage.height(); ++v(1))
			{
				for (v(0) = 0; v(0) < inputImage.width(); ++v(0))
				{
					Vector u = T2 * Rinv * T1 * S * v;
					u /= u(2);
					if (u(0) >= 0 && u(0) < outputImage.width() -0.5 && u(1) >= 0 && u(1) < outputImage.height() -0.5)
					{
						outputImage(v) = inputImage(u);
					}
				}
			}
	}
	catch (std::out_of_range exception)
	{
		std::cout << exception.what() << std::endl;
	}


	outputImage.write_png(argv[2]);

	return 0;
}
