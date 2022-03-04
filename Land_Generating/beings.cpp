#include "beings.h"
#include "world.h"


void Being::Move(const Point& direction, ListBeings being) {
	world->beings[Position.y][Position.x] = ListBeings::EMPTY;
	Position = (Position + direction) % world->WorldSize;
	world->beings[Position.y][Position.x] = being;
}


void Sheep::Simulate() {
	if (age == 0) {       //sheep dies and new flower emerges, either red or violet
		int prob = rand() % (INTERVAL * RANGE);
		if (interval != 1) {
			world->nature.push_back(make_unique<VioletFlower>(Point(Position.x, Position.y), world));
			world->beings[Position.y][Position.x] = ListBeings::VIOLET_FLOWER;
		}
		else {
			world->nature.push_back(make_unique<RedFlower>(Point(Position.x, Position.y), world));
			world->beings[Position.y][Position.x] = ListBeings::RED_FLOWER;
		}

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
			interval = INTERVAL;
		}

		Move(direction, ListBeings::SHEEP);    //sheep moves to new location
	}
	else if (being == ListBeings::SHEEP)
		was_other_sheep = true;
	else if (being == ListBeings::VIOLET_FLOWER)   //flower is eaten when calling Simulate() of VioeltFlower
		modifySheepArray(VIOLET_ADD, result_position);
	else if (being == ListBeings::RED_FLOWER)
		modifySheepArray(RED_ADD, result_position);


	--interval;
	--age;
}

/*
* increase sheep age and change global being in array beings
*/
void Sheep::modifySheepArray(int number, const Point& position) {
	age += number;
	world->beings[position.y][position.x] = ListBeings::SHEEP;
}

void Flower::Simulate() {
	for (int i = -RANGE; i <= RANGE; ++i)
	{
		for (int j = -RANGE; j <= RANGE; ++j) {

			Point direction = Point(i, j);
			ListBeings being = world->GetResultBeing(this, direction);

			if (being == ListBeings::SHEEP) {
				world->EraseBeing(this, &world->nature);
				return;
			}
		}
	}

	--age;
}


void VioletFlower::Simulate() {
	if (age == 0) {       //VioletFlower dies
		world->beings[Position.y][Position.x] = ListBeings::EMPTY;
		world->EraseBeing(this, &world->nature);
		return;
	}
	Flower::Simulate();
}

void RedFlower::Simulate() {
	if (age == 0) {       //RedFlower dies
		world->beings[Position.y][Position.x] = ListBeings::EMPTY;
		world->EraseBeing(this, &world->nature);
		return;
	}
	Flower::Simulate();
}

void Volcano::Simulate() {

}