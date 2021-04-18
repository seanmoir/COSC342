#include "Circle.h"

#include <algorithm>
#include <iostream>

Circle::Circle(int x, int y, int r, const Pixel& colour) : Shape(colour), x_(x), y_(y), r_(r) {}

Circle::Circle(const Circle& circle) : Shape(circle), x_(circle.x_), y_(circle.y_), r_(circle.r_) {}

Circle::~Circle() {}

Circle& Circle::operator=(const Circle& circle) {
	if (this != &circle) {
		Shape::operator=(circle);
		x_ = circle.x_;
		y_ = circle.y_;
		r_ = circle.r_;
	}
	return *this;
}


void Circle::draw(Image& image) const {
	// Make sure we're not drawing out of bounds
	/*int startX = std::max(0, x_);
	int endX = std::min(maxX_ + 1, image.width());
	int startY = std::max(0, minY_);
	int endY = std::min(maxY_ + 1, image.height());*/

	// centre is at (x, y), radius is r, colour is c
	for (auto dy = -r_; dy < r_ + 1; dy++) {
		const auto xrange = sqrt(r_ * r_ - dy * dy);
		for (auto dx = -xrange; dx < xrange + 1; dx++) {
			image(x_ + dx, y_ + dy) = colour_;
		}
	}
}
