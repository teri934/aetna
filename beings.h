#ifndef BEINGS_H_
#define BEINGS_H_

#include <memory>
#include <vector>
#include <string>
#include <iostream>

class Being;
using valptr = std::unique_ptr<Being>;

class Being {
public:
	virtual ~Being() {}
	virtual valptr Clone() = 0;
};


class Sheep : public Being {
public:
	Sheep() {}
	valptr Clone() override { return std::make_unique<Sheep>(*this); }
	const char* PATH = "images/sheep_mini.bmp";
};

class Flower : public Being {
public:
	Flower() {}
	valptr Clone() override { return std::make_unique<Flower>(*this); }
	const char* PATH = "images/flower_mini.bmp";
};


class Volcano : public Being {
public:
	Volcano() {}
	valptr Clone() override { return std::make_unique<Volcano>(*this); }
	const char* PATH = "images/volcano_mini.bmp";
};

#endif // !BEINGS_H_
