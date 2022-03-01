#ifndef HELPER_H_
#define HELPER_H_


/*
* helper structure to store dimensions
*/
struct Size {
	int width;
	int height;

	Size() : width(0), height(0) {};
	Size(int width, int height) : width(width), height(height) {};

	Size operator&= (const Size& s) {
		return Size(s.width, s.height);
	}

};

/*
* 2D vector representation of the position
*/ 
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
			x = (int)s.width - 1;
		if (y < 0)
			y = (int)s.height - 1;

		return Point(x % s.width, y % s.height);
	}

};

#endif
