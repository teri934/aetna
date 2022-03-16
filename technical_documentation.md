# Developer documentation 


## Main Components

### World

This part consists of the the class World which main task is to do the simulation of the imaginary world. In each step the method Simulate() is called and it calls other appropriate methods that take care of beings/objects in the scene. 
\
Except of that the class is responsible placing the right textures in the scene (rendering).

### Beings

The class Beings stores all the beings/objects that can be in the simulation. There is abstract class Being and its derived classes are actors in the scene. There are animate (sheep) and inanimate beings (flowers, volcanos, crosses).
\
Each being has its own overriden method Simulate() which is responsible for its actions in the World.

### Rendering
The rendering part takes care of visualization of the simulation on the screen. So in each step of the simulation the terrain and beings located currently on it must be rendered.
\
Maybe it would be better to create separate rendering class and not to operate it from the World class.

### Perlin noise 

Used for terrain generation ([Perlin Noise](https://www.wikiwand.com/en/Perlin_noise)) in the World part. According to its values for each pixel appropriate intensity is chosen to reflect changing terrain.

## Possible issues

Possible slowing of the simulation when there would be too many objects in the scene so the frame rate would be too low. This could potentially be solved in the future using other rendering approach.
