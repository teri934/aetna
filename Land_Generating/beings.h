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
	VIOLET_FLOWER,
	RED_FLOWER,
	SHEEP,
	VOLCANO,
	EMPTY
};

class Being {
protected:
	World* world = NULL;

	virtual void Move(const Point& direction);
public:
	Point Position;

	virtual being_ptr Clone() = 0;

	//gets ID for type of being
	virtual ListBeings GetBeing() = 0;

	//gets size of the result image in pixels
	virtual Size GetSize() = 0;

	//does one step in discrete simulation
	virtual void Simulate() = 0;

	Being(const Point& p, World* w) : Position(p), world(w) {};
	virtual ~Being() {}
};


class Sheep : public Being {
public:
	Sheep(const Point& position, World* world) : Being(position, world) {}
	being_ptr Clone() override { return std::make_unique<Sheep>(*this); }
	ListBeings GetBeing() override { return ListBeings::SHEEP; }
	Size GetSize() override { return Size(36, 18); }
	void Simulate() override;
};

class VioletFlower : public Being {
public:
	VioletFlower(const Point& position, World* world) : Being(position, world) {}
	being_ptr Clone() override { return std::make_unique<VioletFlower>(*this); }
	ListBeings GetBeing() override { return ListBeings::VIOLET_FLOWER; }
	Size GetSize() override { return Size(24, 12); }
	void Simulate() override;
};

class RedFlower : public Being {
public:
	RedFlower(const Point& position, World* world) : Being(position, world) {}
	being_ptr Clone() override { return std::make_unique<RedFlower>(*this); }
	ListBeings GetBeing() override { return ListBeings::RED_FLOWER; }
	Size GetSize() override { return Size(24, 12); }
	void Simulate() override;
};


class Volcano : public Being {
public:
	Volcano(const Point& position, World* world) : Being(position, world) {}
	being_ptr Clone() override { return std::make_unique<Volcano>(*this); }
	ListBeings GetBeing() override { return ListBeings::VOLCANO; }
	Size GetSize() override { return Size(32, 16); }
	void Simulate() override;

protected:
	void Move(const Point& direction) override {this->Position = Position;}
};

#endif // !BEINGS_H_