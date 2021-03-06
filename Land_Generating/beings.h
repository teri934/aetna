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


/*
*used in simulation to keep track of beings in the scene
*/
enum class ListBeings : Uint8 {
	VIOLET_FLOWER,
	RED_FLOWER,
	SHEEP,
	VOLCANO,
	CROSS,
	EMPTY,
	NO_SHEEP
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
	int age = 100;

	const int RED_ADD = 25;
	const int VIOLET_ADD = 5;
	const int INTERVAL = 40;
	const int TOO_CLOSE = 30;

	void modifySheepArray(int number, const Point& position);
	void createCross();
	bool checkLivingSpace();
	bool checkExplosion();
	bool checkBeing(Point& position);
};

class Flower : public Being {   //common predecessor for VioletFlower and RedFlower
protected:
	void Move(const Point& direction, ListBeings being) override { this->Position = Position; }
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
	Size GetSize() override { return Size(48, 24); }
	void Simulate() override;
	void Explode();
	bool Exploding = false;

protected:
	void Move(const Point& direction, ListBeings being) override {this->Position = Position;}
private:
	int const BORDER = 96;
	int const ADD_WAWE = 48;
	int currentBorder = 0;
};

class Cross : public Being {
public:
	Cross(const Point& position, World* world) : Being(position, world) {}
	ListBeings GetBeing() override { return ListBeings::CROSS; }
	Size GetSize() override { return Size(48, 24); }
	void Simulate() override;

protected:
	void Move(const Point& direction, ListBeings being) override { this->Position = Position; }
private:
	int age = 10;
	const int MULTIPLY = 160;

	ListBeings decideDeathFlowerAndErase();
};

#endif // !BEINGS_H_
