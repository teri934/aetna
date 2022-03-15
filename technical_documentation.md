# Developer documentation 


## Main Components

### World

This part consists of the the class World which main task is to do the simulation of the imaginary world. In each step the method Simulate() is called and it calls other appropriate methods that take care of beings/objects in the scene. Except of that the class is responsible placing the right textures in the scene (rendering).

### Beings

### Rendering

### Perlin noise 

Used for terrain generation ([Perlin Noise](https://www.wikiwand.com/en/Perlin_noise)) in the World part. According to its values for each pixel appropriate intensity is chosen to reflect changing terrain.

## Possible issues

Possible slowing of the simulation when there would be too many objects in the scene so the frame rate would be too high. This could be maybe solved in the future using other rendering approach.
