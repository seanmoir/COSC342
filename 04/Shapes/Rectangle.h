#pragma once

#include "Shape.h"

class Rectangle : public Shape {

public:

	Rectangle(int minX, int minY, int maxX, int maxY, const Pixel& colour);
	Rectangle(const Rectangle& rect);
	~Rectangle();

	Rectangle& operator=(const Rectangle& rect);

	void draw(Image& image) const;

private:

	int minX_, maxX_, minY_, maxY_;

};