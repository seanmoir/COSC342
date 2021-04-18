#include "Rectangle.h"

#include <algorithm>
#include <iostream>

Rectangle::Rectangle(int minX, int minY, int maxX, int maxY, const Pixel& colour) :
	Shape(colour), minX_(minX), minY_(minY), maxX_(maxX), maxY_(maxY) {

}

Rectangle::Rectangle(const Rectangle& rect) : 
	Shape(rect), minX_(rect.minX_), maxX_(rect.maxX_), minY_(rect.minY_), maxY_(rect.maxY_) {
}

Rectangle::~Rectangle() {

}

Rectangle& Rectangle::operator=(const Rectangle& rect) {
	if (this != &rect) {
		Shape::operator=(rect);
		minX_ = rect.minX_;
		maxX_ = rect.maxX_;
		minY_ = rect.minY_;
		maxY_ = rect.maxY_;
	}
	return *this;
}


void Rectangle::draw(Image& image) const {
	// Make sure we're not drawing out of bounds
	int startX = std::max(0, minX_);
	int endX = std::min(maxX_ + 1, image.width());
	int startY = std::max(0, minY_);
	int endY = std::min(maxY_ + 1, image.height());

	for (int y = startY; y < endY; ++y) {
		for (int x = startX; x < endX; ++x) {
			image(x, y) = colour_;
		}
	}
}
