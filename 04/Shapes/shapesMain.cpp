#include <memory>
#include <vector>

#include "Image.h"

#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"

int main() {
	Image image(100, 100);

	std::vector<std::shared_ptr<Shape>> shapes;

	std::shared_ptr<Rectangle> rect1(new Rectangle(20, 20, 80, 80, Pixel(255, 0, 0)));
	shapes.push_back(rect1);
	std::shared_ptr<Rectangle> rect2(new Rectangle(-10, -10, 40, 60, Pixel(0, 255, 0)));
	shapes.push_back(rect2);

	std::shared_ptr<Circle> circle1(new Circle(20, 20, 20, Pixel(0, 0, 255)));
	shapes.push_back(circle1);

	for (auto shape : shapes) {
		shape->draw(image);
	}

	image.write_png("shapes.png");
	
	return 0;
}

