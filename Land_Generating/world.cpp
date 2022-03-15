#include "world.h"
#include <algorithm>

using namespace siv;

/*
* using perlin noise generates terrain with higher and lower regions
*/
void World::generateTerrain(vector<vector<float>>* terrain) {

	PerlinNoise perlin(1234);

	for (size_t y = 0; y < HEIGHT; ++y)
	{
		for (size_t x = 0; x < WIDTH; ++x)
		{
			float value = (float)perlin.accumulatedOctaveNoise2D_0_1(x/fx, y/fy, octaves);
			(*terrain)[y][x] = value;
		}
	}
}

/*
* generating textures from given pictures
*/
void World::generateTextures() {

	for (size_t i = 0; i < paths.size(); i++)
	{
		SDL_Surface* picture = SDL_LoadBMP(paths[i].c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, picture);
		SDL_FreeSurface(picture);
		textures.push_back(move(texture));
	}
}

/*
* generating beings at the beginning of the simulation
*/
void World::generateDefaultBeings() {

	const float LOWLAND = 0.6f;
	const float MIDLAND = 0.4f;
	const float HIGHLAND = 0.2f;
	const float LOW_PROB = SIZE * 0.00001f;
	const float MID_PROB = SIZE * 0.00005f;
	const float HIGH_PROB = SIZE * 0.0002f;

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			int value = rand() % SIZE;


			if (value < LOW_PROB && terrain[y][x] > 0.3f && terrain[y][x] < LOWLAND) {
				Nature.push_back(make_unique<RedFlower>(Point(x, y), this));
				Beings[y][x] = ListBeings::RED_FLOWER;
			}
			else if (value < MID_PROB && terrain[y][x] > MIDLAND) {
				Animals.push_back(make_unique<Sheep>(Point(x, y), this));
				Beings[y][x] = ListBeings::SHEEP;
			}
			else if (value < HIGH_PROB && terrain[y][x] > LOWLAND) {
				Nature.push_back(make_unique<VioletFlower>(Point(x, y), this));
				Beings[y][x] = ListBeings::VIOLET_FLOWER;
			}
			else if (value < MID_PROB && terrain[y][x] < HIGHLAND) {
				Volcanos.push_back(make_unique<Volcano>(Point(x, y), this));
				Beings[y][x] = ListBeings::VOLCANO;
			}
			else
				Beings[y][x] = ListBeings::EMPTY;

		}
	}
}




/*
* locking texture so the values of pixels in interal buffer can be updated
*/
void World::LockAndRender(SDL_Texture* texture, bool exploding) {

	unsigned char* pixels = nullptr;
	int pitch = 0;
	SDL_LockTexture
	(
		texture,
		NULL,
		reinterpret_cast<void**>(&pixels),
		&pitch
	);

	if (!exploding)  //choose the rendering
		RenderTerrain(pixels);
	else
		RenderExplosions(pixels);

	SDL_UnlockTexture(texture);
}

/*
* applies to perlin-noise-generated terrain colors and writes it to the target bitmap
*/
void World::RenderTerrain(unsigned char* target) {

	for (size_t y = 0; y < HEIGHT; ++y)
	{
		for (size_t x = 0; x < WIDTH; ++x)
		{
			float floor_value = ((float)(floor)(terrain[y][x] * MULTI)) / MULTI;
			assignPixels(target, y, x, HUE_TERRAIN, floor_value);
		}
	}
}


/*
* visualizes explosion waves from volcano
*/
void World::RenderExplosions(unsigned char* target) {
	for (size_t y = 0; y < HEIGHT; ++y)
	{
		for (size_t x = 0; x < WIDTH; ++x)
		{
			if (!ExplosionTerrain[y][x]) {
				float floor_value = ((float)(floor)(terrain[y][x] * MULTI)) / MULTI;
				assignPixels(target, y, x, HUE_TERRAIN, floor_value);
			}
			else
				assignPixels(target, y, x, HUE_EXPLOSION, 1);
		}
	}

}

/*
* converts HSV to RGB and low level values to "pixel array" assignement
*/
void World::assignPixels(unsigned char* target, size_t y, size_t x, const size_t HUE, float value) {
	vector<int> colors = Converter::hsvToRgb(HUE / FULL_CIRCLE, 1, value);
	size_t current_pixel = static_cast<size_t>(3) * (y * WIDTH + x);
	target[current_pixel + static_cast<uint8_t>(Color::R)] = colors[static_cast<uint8_t>(Color::R)];
	target[current_pixel + static_cast<uint8_t>(Color::G)] = colors[static_cast<uint8_t>(Color::G)];
	target[current_pixel + static_cast<uint8_t>(Color::B)] = colors[static_cast<uint8_t>(Color::B)];
}

/*
* calls specific rendering function for every array in simulation
*/
void World::RenderBeings() {

	renderArray(&Volcanos);
	renderArray(&Objects);
	renderArray(&Nature);
	renderArray(&Animals);
}

/*
* from the given array takes the correct textures and "glues" it to the result bitmap
*/
void World::renderArray(vector<being_ptr>* arr){
	SDL_Rect rect;
	for (size_t i = 0; i < arr->size(); ++i)
	{
		rect.w = (*arr)[i]->GetSize().width;
		rect.h = (*arr)[i]->GetSize().height;
		rect.x = (*arr)[i]->Position.x - (rect.w >> 1);
		rect.y = (*arr)[i]->Position.y - (rect.h >> 1);

		auto ID = static_cast<uint8_t>((*arr)[i]->GetBeing());
		SDL_RenderCopy(renderer, textures[ID], NULL, &rect);
	}
}

/*
* renders menu on the side
*/
void World::RenderMenu() {
	SDL_RenderCopy(renderer, textures[textures.size()-1], NULL, &menu);

	SDL_Rect rect;
	rect.w = menu.w;
	rect.h = stepMenu;
	rect.x = xMenu;
	for (int i = 0; i < textures.size()-2; ++i)  //without cross and background menu texture
	{
		rect.y = i * stepMenu + paddingMenu;
		SDL_RenderCopy(renderer, textures[i], NULL, &rect);
	}
}




/*
* for every being calls its simulate method
*/
void World::Simulate() {
	for (size_t i = 0; i < Nature.size(); ++i)
		Nature[i]->Simulate();

	for (size_t i = 0; i < Animals.size(); ++i)
		Animals[i]->Simulate();

	for (size_t i = 0; i < Volcanos.size(); ++i)
		Volcanos[i]->Simulate();

	for (size_t i = 0; i < Objects.size(); ++i)
		Objects[i]->Simulate();
}

bool World::CheckExplodingVolcanos() {

	for (size_t i = 0; i < Volcanos.size(); ++i)
	{
		if (dynamic_cast<Volcano*>(Volcanos[i].get())->Exploding)
			return true;
	}

	Exploding = false;

	fill(ExplosionTerrain.begin(), ExplosionTerrain.end(), vector<bool>(WIDTH, false));
	return false;
}

Point World::GetResultPosition(Being* being, const Point& direction) {
	return (being->Position + direction) % WorldSize;
}

ListBeings World::GetResultBeing(Being* being, Point& direction) {
	Point result_position = GetResultPosition(being, direction);
	return Beings[result_position.y][result_position.x];
}

/*
* erasing being from the vector of current "alive" animals so it is not rendered again
*/
void World::EraseBeing(Being* being, vector<being_ptr>* arr, ListBeings newBeing) {
	Beings[being->Position.y][being->Position.x] = newBeing;
	for (int i = ((int)(*arr).size() - 1); i > -1; --i)
	{
		if ((*arr)[i]->Position.x == being->Position.x && (*arr)[i]->Position.y == being->Position.y) {
			(*arr).erase((*arr).begin() + i);
			return;
		}

	}
}





void World::CheckClick(unsigned int x, unsigned int y) {

	if(!checkMenuFigures(x, y))   //checking clicking on the volcanos if no menu figure was clicked
		checkVolcanos(x, y);
}

void World::CheckUnclick(unsigned int x, unsigned int y) {
	if (ClickMenu) {
		ClickMenu = false;

		if (Beings[y][x] != ListBeings::EMPTY)
			return;

		switch (indexFigure) {

		case static_cast<uint8_t>(ListBeings::VIOLET_FLOWER):
			Nature.push_back(make_unique<VioletFlower>(Point(x, y), this));
			Beings[y][x] = ListBeings::VIOLET_FLOWER;
			break;
		case static_cast < uint8_t>(ListBeings::RED_FLOWER):
			Nature.push_back(make_unique<RedFlower>(Point(x, y), this));
			Beings[y][x] = ListBeings::RED_FLOWER;
			break;
		case static_cast <uint8_t>(ListBeings::SHEEP):
			Animals.push_back(make_unique<Sheep>(Point(x, y), this));
			Beings[y][x] = ListBeings::SHEEP;
			break;
		case static_cast <uint8_t>(ListBeings::VOLCANO):
			Volcanos.push_back(make_unique<Volcano>(Point(x, y), this));
			Beings[y][x] = ListBeings::VOLCANO;
			break;
		default:
			break;
		}
;
	}
}

/*
* checking if user clicked on a volcano
* then calling function for its explosion
*/
void World::checkVolcanos(unsigned int x, unsigned int y) {
	if (Volcanos.size() == 0)
		return;

	int width = Volcanos[0]->GetSize().width >> 1;
	int height = Volcanos[0]->GetSize().height >> 1;

	int x_min = x - width;
	int x_max = x + width;
	int y_min = y - height;
	int y_max = y + height;

	for (size_t i = 0; i < Volcanos.size(); i++)
	{
		if (Volcanos[i]->Position.x >= x_min && Volcanos[i]->Position.x <= x_max && Volcanos[i]->Position.y >= y_min && Volcanos[i]->Position.y <= y_max)
			dynamic_cast<Volcano*>(Volcanos[i].get())->Explode();
	}
}

bool World::checkMenuFigures(unsigned int x, unsigned int y) {

	for (int i = 0; i < textures.size() - 2; ++i)
	{
		if (checkFigure(x, y, i))
			return true;
	}

	return false;
}


bool World::checkFigure(unsigned int x, unsigned int y, int index) {

	int x_min = x - sizeMenu.width;
	int x_max = x + (sizeMenu.width >> 1);
	int y_min = y - sizeMenu.height;
	int y_max = y + sizeMenu.height;



	int yMenu = index * stepMenu + paddingMenu;
	if (xMenu >= x_min && xMenu <= x_max && yMenu >= y_min && yMenu <= y_max) {
		ClickMenu = true;
		indexFigure = index;
		return true;
	}

	return false;
}

