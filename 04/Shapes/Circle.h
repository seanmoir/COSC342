#pragma once

#include "Shape.h"

class Circle : public Shape {

public:

	Circle(int x, int y, int r, const Pixel& colour);
	Circle(const Circle& circle);
	~Circle();

	Circle& operator=(const Circle& circle);

	void draw(Image& image) const;

private:

	int x_, y_, r_;

};