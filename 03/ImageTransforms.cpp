
// Simple, portable image I/O libraries
#include "Image.h"

// Standard I/O
#include <iostream>

// Will be needed for trigonometric functions
#include <cmath>

int main(int argc, char *argv[]) {

	// Expecting two arguments
	if (argc != 3) {
		std::cout << "Usage: ImageTransforms <input image> <output image>" << std::endl;
		exit(-1);
	}

	Image inputImage;

	inputImage.read(argv[1]);

	Image outputImage(inputImage.width(), inputImage.height());
	try {
		for (int y = 0; y < inputImage.height(); ++y) {
			for (int x = 0; x < inputImage.width(); ++x) {
				outputImage(x, y) = inputImage(x, y);
			}
		}
	} catch (std::out_of_range exception) {
		std::cout << exception.what() << std::endl;
	}
	outputImage.write_png(argv[2]);

    return 0;
}

