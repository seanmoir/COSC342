#pragma once

struct Pixel {
	Pixel() : r(0), g(0), b(0) {}
	Pixel(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}
	unsigned char r, g, b;
};
