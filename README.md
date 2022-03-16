# aetna 🌋🐑

### Aetna is a simulation of imaginary land with its inhabitants.
[Developer Documentation](./technical_documentation.md)

<img src="./Land_Generating/images/simulation.png" width = 600>

## Terrain

Terrain is generated using [Perlin noise](https://www.wikiwand.com/en/Perlin_noise) and the corresponding color intensities are assigned according to its values.  At the beginning you can choose octaves and frequencies to your liking.
</br></br>
<img src="./Land_Generating/images/terrain.png">


## Inhabitants

### Violet flower
Adds some living years to sheep that has eaten it and it emerges instead of cross after some time.
</br></br>
<img src="./Land_Generating/images/violet_flower_mini.bmp">

</br></br>

### Red flower
Adds some living years to sheep that has eaten it (more than violet one) and it emerges instead of cross after some time.

</br></br>
<img src="./Land_Generating/images/red_flower_mini.bmp">


</br></br>

### Sheep
A living creature moving randomly. It eats flowers and has bigger life span than flowers.
</br></br>
<img src="./Land_Generating/images/sheep_mini.bmp">


</br></br>

### Cross
When a sheep dies it emerges on that place for a little time.
</br></br>
<img src="./Land_Generating/images/cross_mini.bmp">


</br></br>

### Volcano
Volcano explodes and simulation slows down when clicking on it and it kills all the sheep around it that are close enough.
</br></br>
<img src="./Land_Generating/images/volcano_mini.bmp">


## Menu

In the menu you have the possibility to choose which figure to add to the simulation scene. Just click on a figure in the menu and then drag it somewhere on the simulation terrain: the new being/object will appear there (not in case if you click exactly on pixel having something there).

</br></br>
<img src="./Land_Generating/images/menu.png">
