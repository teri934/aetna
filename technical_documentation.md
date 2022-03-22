# Developer documentation 


## Main Components


### World
This part consists of the the class World which main task is to do the simulation of the imaginary world. In each step the method Simulate() is called and it calls other appropriate methods that take care of beings/objects in the scene. 
\
Except of that the class is responsible placing the right textures in the scene (rendering).

#### API
Important methods:
* Simulate() -> calls appropriate methods simulating every Being
* generateTerrain(vector<vector<float>>* terrain) -> generating terrain using Perlin Noise
* generateDefaultBeings() -> according to given probabilities generates Beings at the beginning of the simulation

Then there are methods for rendering such as RenderTerrain(unsigned char* target), RenderExplosions(unsigned char* target), RenderMenu(), RenderBeings()...

#### Interactions
In each step of the simulation each Being behaves according to ist definition:
* Sheep
	* moves in randomly chosen direction
	* when two sheep are close enough and after some interval new sheep 
	* when sheep doesn't have enough living space it dies
	* when eating flower it adds some years to ist life
* Flower
	* two variants: violet or red
	* violet one adds 5 years to sheep's lifespan
	* red one adds 25 years to sheep's lifespan
* Cross
	* emerges after sheep's death and disappers after some time
	* it is replaced by a flower
* Volcano
	* explodes after clicking on it
	* kills sheep that are near proximity
	


### Beings
The class Beings stores all the Beings/objects that can be in the simulation. There is abstract class Being and its derived classes are actors in the scene. There are animate (sheep) and inanimate beings (flowers, volcanos, crosses).
\
Each being has its own overriden method Simulate() which is responsible for its actions in the World.

#### API

Methods that have to be implemented by every class inheriting from Being:
* ListBeings GetBeing() -> returns enum ID of the being
* Size GetSize() -> returns 2D vector of result size that is rendered
* Simulate() -> defines behavior for being in each step of the simulation

Constructor Being(const Point& p, World* w) initializes Being with its location at the beginning and its pointer on the simulation (World* world)


### Rendering
The rendering part takes care of visualization of the simulation on the screen. So in each step of the simulation the terrain and beings located currently on it must be rendered.
\
Maybe it would be better to create separate rendering class and not to operate it from the World class.

### Perlin noise 

Used for terrain generation ([Perlin Noise](https://www.wikiwand.com/en/Perlin_noise)) in the World part. According to its values for each pixel appropriate intensity is chosen to reflect changing terrain.


## Possible issues

Possible slowing of the simulation when there would be too many objects in the scene so the frame rate would be too low. This could potentially be solved in the future using other rendering approach.
