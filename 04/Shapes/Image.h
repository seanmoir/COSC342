#pragma once

#include "Pixel.h"

#include <string>
#include <vector>


class Image {

public:

	Image();
	Image(const Image& image);
	Image(int width, int height);
	~Image();

	Image& operator=(const Image& image);

	const int& width() { return width_; }
	const int& height() { return height_; }

	Pixel& operator()(int x, int y);

	const Pixel& operator()(int x, int y) const;

	bool read(std::string filename);
	bool write_png(std::string filename);

private:

	int width_, height_;
	std::vector<Pixel> pixels_;
};