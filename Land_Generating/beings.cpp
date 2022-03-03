#include "beings.h"
#include "world.h"


void Being::Move(const Point& direction, ListBeings being) {
	world->beings[Position.y][Position.x] = ListBeings::EMPTY;
	Position = (Position + direction) % world->WorldSize;
	world->beings[Position.y][Position.x] = being;
}


void Sheep::Simulate() {
	if (age == 0) {       //sheep dies and new flower emerges
		world->nature.push_back(make_unique<VioletFlower>(Point(Position.x, Position.y), world));
		world->beings[Position.y][Position.x] = ListBeings::VIOLET_FLOWER;
		world->EraseBeing(this, &world->animals);
		return;
	}

	int x_direction = (rand() % STEP) - RANGE;  //random position where to move
	int y_direction = (rand() % STEP) - RANGE;

	Point direction = Point(x_direction, y_direction);
	Point result_position = world->GetResultPosition(this, direction);
	ListBeings being = world->beings[result_position.y][result_position.x];

	if (being == ListBeings::EMPTY) {

		if (was_other_sheep && interval < 0) {     //new sheep is "born" if in tha last step two sheep were close enough and some time has passed
			world->animals.push_back(make_unique<Sheep>(Point(result_position.x, result_position.y), world));
			world->beings[result_position.y][result_position.x] = ListBeings::SHEEP;
			was_other_sheep = false;
			interval = 10;
		}

		Move(direction, ListBeings::SHEEP);    //sheep moves to new location
	}
	else if (being == ListBeings::SHEEP) {
		was_other_sheep = true;
	}

	--interval;
	--age;
}

void VioletFlower::Simulate() {
	for (int i = -3; i <= 3; ++i)
	{
		for (int j = -3; j <= 3; ++j) {

			Point direction = Point(i, j);
			ListBeings being = world->GetResultBeing(this, direction);

			if (being == ListBeings::SHEEP) {
				world->EraseBeing(this, &world->nature);
				return;
			}
		}
	}
}

void RedFlower::Simulate() {

}

void Volcano::Simulate() {

}