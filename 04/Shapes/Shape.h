#pragma once

#include "Image.h"
#include "Pixel.h"

class Shape {

public:

	Shape(const Pixel& colour);
	Shape(const Shape& shape);
	virtual ~Shape();

	Shape& operator=(const Shape& shape);

	virtual void draw(Image& image) const = 0;

	void setColour(Pixel colour);

protected:

	Pixel colour_;

};