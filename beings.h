#ifndef BEINGS_H_
#define BEINGS_H_

#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include "helper.h"

class World;

class Being;
using valptr = std::unique_ptr<Being>;

class Being {
protected:
	World* world;

	virtual void Move(const Point& direction) {
		position = position + direction;
	}
public:
	Point position;
	virtual valptr Clone() = 0;

	Being() {};
	Being(const Point& p, World* w) : position(p), world(w) {};
	virtual ~Being() {}
};


class Sheep : public Being {
public:
	Sheep(Point& position, World* world) : Being(position, world) {}
	valptr Clone() override { return std::make_unique<Sheep>(*this); }
	const char* PATH = "images/sheep_mini.bmp";
};

class Flower : public Being {
public:
	Flower(Point& position, World* world) : Being(position, world) {}
	valptr Clone() override { return std::make_unique<Flower>(*this); }
	const char* PATH = "images/flower_mini.bmp";
};


class Volcano : public Being {
public:
	Volcano(Point& position, World* world) : Being(position, world) {}
	valptr Clone() override { return std::make_unique<Volcano>(*this); }
	const char* PATH = "images/volcano_mini.bmp";

protected:
	void Move(const Point& direction) override {this->position = position;}
};

#endif // !BEINGS_H_
