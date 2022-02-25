#ifndef BEINGS_H_
#define BEINGS_H_

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <SDL.h>

#include "helper.h"

class World;

class Being;
using being_ptr = std::unique_ptr<Being>;

enum class ListBeings : Uint8 {
	FLOWER,
	SHEEP,
	VOLCANO
};

class Being {
protected:
	World* world = NULL;

	virtual void Move(const Point& direction) {
		position = position + direction;
	}
public:
	Point position;
	virtual being_ptr Clone() = 0;
	virtual ListBeings GetBeing() = 0;

	Being(const Point& p, World* w) : position(p), world(w) {};
	virtual ~Being() {}
};


class Sheep : public Being {
public:
	Sheep(const Point& position, World* world) : Being(position, world) {}
	being_ptr Clone() override { return std::make_unique<Sheep>(*this); }
	ListBeings GetBeing() override { return ListBeings::SHEEP; }
};

class Flower : public Being {
public:
	Flower(const Point& position, World* world) : Being(position, world) {}
	being_ptr Clone() override { return std::make_unique<Flower>(*this); }
	ListBeings GetBeing() override { return ListBeings::FLOWER; }
};


class Volcano : public Being {
public:
	Volcano(const Point& position, World* world) : Being(position, world) {}
	being_ptr Clone() override { return std::make_unique<Volcano>(*this); }
	ListBeings GetBeing() override { return ListBeings::VOLCANO; }

protected:
	void Move(const Point& direction) override {this->position = position;}
};

#endif // !BEINGS_H_
