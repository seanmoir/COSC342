#include "Shape.h"

Shape::Shape(const Pixel& colour) : colour_(colour) {}

Shape::Shape(const Shape& shape) : colour_(shape.colour_) {}

Shape::~Shape() {}

Shape& Shape::operator=(const Shape& shape) {
	if (this != &shape) {
		colour_ = shape.colour_;
	}
	return *this;
}


void Shape::setColour(Pixel colour) {
	colour_ = colour;
}
