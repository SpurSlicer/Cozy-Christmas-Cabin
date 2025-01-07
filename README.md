## WARNING!!
This project uses libpng!! Please install it before running this.

## Compilation
```shell
make; ./final
```

## Controls
- WASD: move
- Mouse: look around
- \>: open/close west window
- <: open/close east window
- m: extinguish/light the fire
- space: pause mouse camera movement 

## NOTABLE FEATURES [80 hours]
- Custom made object loader that can load .obj files with up to 16-sided polygons and implements an efficient batch draw to save computation power with texture loading
- Snow particle generator that spawns falling snow flakes at random velocities in a random position
- Windows open and close upon pressing \> and < keys
- Extinguishing the fire (press m) removes lighting and makes the scene dark
- Fire shader with the base implemented by a tutorial with changes made (sinusodial alpha distortion and improved distortion complexity) for a more realistic affect
- Smoke shader with the base implemented from the fire tuotiral but with dimension reduced distortion as smoke doesn't need a noise filter and modified scrolling speeds
- Alpha blended ash texture under the fire
- Transparency shaders to remove the background of images (no png transparency was used);
- Libpng integration
- Music
- Collision implementation
- **Complex Objects**: The tree and the star
- **Used .OBJ Objects**: The chair and the bookcase (chair used to show efficacy of loader as it has 10000 polygons)

## IMPLEMENTATION DETAILS
This code uses an object oriented approach; specifically, it utilizes inheritance to provide native functions to all themed object loaders (house, tree, etc.). It allows for the easy loading of any type of object, the application of any shader, texture, etc. The particle generator manages its own memory and deletes snowflakes once they pass y = 0. 

## REUSED CODE 
- Fire shader was from a tutorial (https://rastertek.com/gl4linuxtut33.html) but I made a good amount of improvements to make it look nicer (see notes on it above).
- Smoke shader uses the same base as the fire shader but was reworked quite a bit to not use noise scrolling (again see notes above)
- Texture loading with libpng came from http://tfc.duke.free.fr/coding/src/png.c. Very few changes were made.
- Object loading started with this base: https://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/ but ALMOST ALL OF IT was completely reworked. The only remnant of the base is really the if/elseif chain. 
