#ifndef HELPER_H_
#define HELPER_H_

struct Point {
	int x;
	int y;

	Point() : x(0), y(0) {};
	Point(int a, int b) : x(a), y(b) {};

	Point operator= (const Point& p) {
		return Point(p.x, p.y);
	}

	Point operator+ (const Point& p) {
		return Point(x + p.x, y + p.y);
	}

};

#endif
