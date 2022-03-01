#include "beings.h"
#include "world.h"


void Being::Move(const Point& direction) {
	Position = (Position + direction) % world->WorldSize;
}


void Sheep::Simulate() {

	int x_direction = (rand() % 8) - 4;
	int y_direction = (rand() % 8) - 4;

	Point direction = Point(x_direction, y_direction);
	Point result_position = world->GetResultPosition(this, direction);
	ListBeings being = world->beings[result_position.y][result_position.x];

	if (being == ListBeings::EMPTY) {

		Move(direction);
		return;
	}

}

void VioletFlower::Simulate() {

}

void RedFlower::Simulate() {

}

void Volcano::Simulate() {

}