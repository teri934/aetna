#ifndef HELPER_H_
#define HELPER_H_

struct Point {
	size_t x;
	size_t y;

	Point() : x(0), y(0) {};
	Point(size_t a, size_t b) : x(a), y(b) {};

	Point operator= (const Point& p) {
		return Point(p.x, p.y);
	}

	Point operator+ (const Point& p) {
		return Point(x + p.x, y + p.y);
	}

};

#endif
