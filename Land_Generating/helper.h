#ifndef HELPER_H_
#define HELPER_H_

struct Point {
	size_t x;
	size_t y;

	Point() : x(0), y(0) {};
	Point(size_t x, size_t y) : x(x), y(y) {};

	Point operator= (const Point& p) {
		return Point(p.x, p.y);
	}

	Point operator+ (const Point& p) {
		return Point(x + p.x, y + p.y);
	}

};

struct Size {
	size_t width;
	size_t height;

	Size() : width(0), height(0) {};
	Size(size_t width, size_t height) : width(width), height(height) {};

	Size operator= (const Size& s) {
		return Size(s.width, s.height);
	}

};

#endif
