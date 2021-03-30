#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
// Uncomment this for MS Visual Studio
// #define STBI_MSC_SECURE_CRT
#include "stb_image_write.h"

#include <exception>
#include <memory>

Image::Image() : width_(0), height_(0), pixels_() {

}

Image::Image(const Image& image) : width_(image.width_), height_(image.height_), pixels_(image.pixels_) {

}

Image::Image(int width, int height) : width_(width), height_(height), pixels_(width*height) {

}


Image::~Image() {

}

Image& Image::operator=(const Image& image) {
	if (this != &image) {
		width_ = image.width_;
		height_ = image.height_;
		pixels_ = image.pixels_;
	}
	return *this;
}


Pixel& Image::operator()(int x, int y) {
	if (x < 0 || x >= width_ ||
		y < 0 || y >= height_) {
		throw std::out_of_range("co-ordinates out of range");
	}

	return pixels_[y*width_ + x];
}

const Pixel& Image::operator()(int x, int y) const {
	if (x < 0 || x >= width_ ||
		y < 0 || y >= height_) {
		throw std::out_of_range("co-ordinates out of range");
	}

	return pixels_[y*width_ + x];
}



bool Image::read(std::string filename) {
	int sizeX, sizeY, d;
	unsigned char *data = stbi_load(filename.c_str(), &sizeX, &sizeY, &d, 3);
	width_ = sizeX;
	height_ = sizeY;
	pixels_.resize(width_*height_);
	if (data) {
		for (size_t ix = 0; ix < width_*height_; ++ix) {
			pixels_[ix].r = data[3 * ix];
			pixels_[ix].g = data[3 * ix + 1];
			pixels_[ix].b = data[3 * ix + 2];
		}
		stbi_image_free(data);
		return true;
	}
	return false;
}

bool Image::write_png(std::string filename) {
	std::unique_ptr<unsigned char[]> data(new unsigned char[width_ * height_ * 3]);
	for (size_t ix = 0; ix < width_*height_; ++ix) {
		data[3 * ix] = pixels_[ix].r;
		data[3 * ix + 1] = pixels_[ix].g;
		data[3 * ix + 2] = pixels_[ix].b;
	}
	stbi_write_png(filename.c_str(), width_, height_, 3, data.get(), width_ * 3);
	return false;
}