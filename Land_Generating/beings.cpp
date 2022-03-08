#include "beings.h"
#include "world.h"


void Being::Move(const Point& direction, ListBeings being) {
	world->Beings[Position.y][Position.x] = ListBeings::EMPTY;
	Position = (Position + direction) % world->WorldSize;
	world->Beings[Position.y][Position.x] = being;
}


void Sheep::Simulate() {

	if (age == 0 || !checkLivingSpace() || checkExplosion()) {   //sheep dies and new flower emerges, either red or violet
		decideDeathFlowerAndErase();
		return;
	}

	int x_direction = (rand() % STEP) - RANGE;  //random position where to move
	int y_direction = (rand() % STEP) - RANGE;

	Point direction = Point(x_direction, y_direction);
	Point result_position = world->GetResultPosition(this, direction);
	ListBeings being = world->Beings[result_position.y][result_position.x];

	if (being == ListBeings::EMPTY && !checkBeing(direction)) {

		if (was_other_sheep && interval < 0 && age > INTERVAL) {     //new sheep is "born" if in tha last step two sheep were close enough and some time has passed and is not too old
			world->Animals.push_back(make_unique<Sheep>(Point(result_position.x, result_position.y), world));
			world->Beings[result_position.y][result_position.x] = ListBeings::SHEEP;
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
* choosig which flower grows after sheep's death
*/
void Sheep::decideDeathFlowerAndErase() {

	int value = rand() % (INTERVAL * RANGE);
	if (value > 10) {
		world->Nature.push_back(make_unique<VioletFlower>(Point(Position.x, Position.y), world));
		world->Beings[Position.y][Position.x] = ListBeings::VIOLET_FLOWER;
	}
	else {
		world->Nature.push_back(make_unique<RedFlower>(Point(Position.x, Position.y), world));
		world->Beings[Position.y][Position.x] = ListBeings::RED_FLOWER;
	}

	world->EraseBeing(this, &world->Animals);
}

/*
* checking if other volcano is not too close so sheep wouldn't "walk" on it
*/
bool Sheep::checkBeing(Point& result_direction) {

	for (int i = -TOO_CLOSE; i < TOO_CLOSE; ++i)
	{
		for (int j = -TOO_CLOSE; j < TOO_CLOSE; ++j)
		{
			Point direction = Point(i, j);
			Point result_position = world->GetResultPosition(this, result_direction + direction);
			ListBeings being = world->Beings[result_position.y][result_position.x];

			if (being == ListBeings::VOLCANO) {
				std::cout << "too close\n";
				return true;
			}
		}
	}

	return false;
}

/*
* checking if at least one neighboring field (pixel) is sheep-free
* else not enough living space -> return false
*/
bool Sheep::checkLivingSpace() {

	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			Point direction = Point(i, j);
			Point result_position = world->GetResultPosition(this, direction);
			ListBeings being = world->Beings[result_position.y][result_position.x];

			if (being != ListBeings::SHEEP)
				return true;
		}
	}

	return false;
}

/*
* checking if the current sheep died because of explosion
*/
bool Sheep::checkExplosion() {

	ListBeings being = world->Beings[Position.y][Position.x];
	if (being == ListBeings::NO_SHEEP)
		return true;

	return false;
}

/*
* increase sheep age and change global being in array beings
*/
void Sheep::modifySheepArray(int number, const Point& position) {
	age += number;
	world->Beings[position.y][position.x] = ListBeings::SHEEP;
}

void Flower::Simulate() {
	for (int i = -RANGE; i <= RANGE; ++i)
	{
		for (int j = -RANGE; j <= RANGE; ++j) {

			Point direction = Point(i, j);
			ListBeings being = world->GetResultBeing(this, direction);

			if (being == ListBeings::SHEEP) {
				world->EraseBeing(this, &world->Nature);
				return;
			}
		}
	}

	--age;
}


void VioletFlower::Simulate() {
	if (age == 0) {       //VioletFlower dies
		world->Beings[Position.y][Position.x] = ListBeings::EMPTY;
		world->EraseBeing(this, &world->Nature);
		return;
	}
	Flower::Simulate();
}

void RedFlower::Simulate() {
	if (age == 0) {       //RedFlower dies
		world->Beings[Position.y][Position.x] = ListBeings::EMPTY;
		world->EraseBeing(this, &world->Nature);
		return;
	}
	Flower::Simulate();
}

void Volcano::Simulate() {

	if (exploding && currentBorder < BORDER) {
		int new_current_border = currentBorder + ADD_WAWE;

		for(int i = -currentBorder; i < new_current_border; ++i)
		{
			for (int j = -currentBorder; j < new_current_border; ++j)
			{
				Point direction = Point(i, j);
				Point result_position = world->GetResultPosition(this, direction);
				ListBeings being = world->Beings[result_position.y][result_position.x];

				if (being == ListBeings::SHEEP)
					world->Beings[result_position.y][result_position.x] = ListBeings::NO_SHEEP;
			}
		}

		currentBorder = new_current_border;
	}
	else if (exploding)
		exploding = false;
}

/*
* preparing for the explosion
*/
void Volcano::Explode() {
	currentBorder = 0;
	exploding = true;
}