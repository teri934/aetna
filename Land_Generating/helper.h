#ifndef HELPER_H_
#define HELPER_H_


struct Size {
	size_t width;
	size_t height;

	Size() : width(0), height(0) {};
	Size(size_t width, size_t height) : width(width), height(height) {};

	Size operator&= (const Size& s) {
		return Size(s.width, s.height);
	}

};

struct Point {
	int x;
	int y;

	Point() : x(0), y(0) {};
	Point(int x, int y) : x(x), y(y) {};

	Point operator&= (const Point& p) {
		return Point(p.x, p.y);
	}

	Point operator+ (const Point& p) {
		return Point(x + p.x, y + p.y);
	}

	Point operator% (const Size& s) {
		if (x < 0)
			x = s.width - 1;
		if (y < 0)
			y = s.height - 1;

		return Point(x % s.width, y % s.height);
	}

};

#endif
