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
	const int STEP = 8;
	const int RANGE = 4;
	int age = 0;

	/*
	*moves being from one point to another
	*/
	virtual void Move(const Point& direction, ListBeings being);
public:
	Point Position;


	/*
	* gets ID for type of being
	*/
	virtual ListBeings GetBeing() = 0;

	/*
	* gets size of the result image in pixels
	*/
	virtual Size GetSize() = 0;

	/*
	* does one step in discrete simulation
	*/
	virtual void Simulate() = 0;

	Being(const Point& p, World* w) : Position(p), world(w) {};
	virtual ~Being() {}
};


class Sheep : public Being {
public:
	Sheep(const Point& position, World* world) : Being(position, world) {}
	ListBeings GetBeing() override { return ListBeings::SHEEP; }
	Size GetSize() override { return Size(36, 18); }
	void Simulate() override;
private:
	bool was_other_sheep = false;
	int interval = 10;
	int age = 50;

	const int RED_ADD = 25;
	const int VIOLET_ADD = 5;
	const int INTERVAL = 10;

	void modifySheepArray(int number, const Point& position);
};

class Flower : public Being {   //common predecessor for VioletFlower and RedFlower
public:
	Flower(const Point& position, World* world) : Being(position, world) {}
	ListBeings GetBeing() override { return ListBeings::EMPTY; }
	Size GetSize() override { return Size(0, 0); }
	void Simulate() override;

protected:
	int age = 20;
};

class VioletFlower : public Flower {
public:
	VioletFlower(const Point& position, World* world) : Flower(position, world) {}
	ListBeings GetBeing() override { return ListBeings::VIOLET_FLOWER; }
	Size GetSize() override { return Size(24, 12); }
	void Simulate() override;
};

class RedFlower : public Flower {
public:
	RedFlower(const Point& position, World* world) : Flower(position, world) {}
	ListBeings GetBeing() override { return ListBeings::RED_FLOWER; }
	Size GetSize() override { return Size(24, 12); }
	void Simulate() override;
};


class Volcano : public Being {
public:
	Volcano(const Point& position, World* world) : Being(position, world) {}
	ListBeings GetBeing() override { return ListBeings::VOLCANO; }
	Size GetSize() override { return Size(32, 16); }
	void Simulate() override;

protected:
	void Move(const Point& direction, ListBeings being) override {this->Position = Position;}
};

#endif // !BEINGS_H_
