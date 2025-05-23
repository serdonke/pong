# Pong

#### Video demo: https://youtu.be/KllknKDsSJU
#### Description: Pong Clone using C and [raylib](https://github.com/raylib.git)

This was fun!

I started CS50X way back in 2021 but could not finish because reasons.

I came back with the resolve to finish it and move on to other things that are more inline with my interest in programming(Gamedev, definitely checking out GD50 next).

Initially when I was doing CS50 I had decided to submit as my final project a Chicken Invaders clone(this was included with many Windows XP distributions when I started using computers at a young age), of course this was not possible to do with my skills when I worked on this as I had just finished with Week 7 of CS50x (I was not at all interested in the Webdev stuff).

I then rescoped my final project and decided to do Pong on my own, there was the GD50 thing but I did not like Lua at that time and decided to use C and searched for libraries that I could use to make games.

I decided on [raylib](https://github.com/raysan5/raylib.git) which introduced itself as "A simple and easy-to-use library to enjoy videogames programming", I mean its simple as in it does not expose a lot of functionality like SDL and other libs but powerful and feature complete that you would not miss a lot of stuff.

Here's a run down of the project files:

There are not a lot of source code files (but sure a lot of build files), as I wanted to keep this simple, the game is fully implemented in `pong.c`.

Raylib provides many structures by default, they are very simple in their own and so I decided to use those for the game, the player and AI objects needed rectangles for their body and that is provided by raylib, its a basic struct with four floats, two denotes its position in the 2D plane and other two its size.

I then used those to create a type of my own (Paddle) which had a rectangle and, an `int` for score and another variable that has a color (whichi again is a type defined by raylib), this is the basic player and AI structure (or GameObjects).

Then I created a Ball, there is no circle structure and we do not need one, since the rendering functions only require radius, color and position.

By default the game launches and is single player only, adding two players mode is trivial, but I guess anybody auditing or testing will not bother gathering somebody to play hence the current state.

The game uses very basic collision detections to prevent the ball and paddle from leaving the screen, for the interaction between ball and paddle however the game uses raylib's `CheckCollisionCircleRec()` in built function.

I took this oppurtunity to learn a bit more about several build systems that support building C/C++ and found that almost all of them suck.

I am using Cmake which should support building for Windows (not tested) and Linux. 

`Makefile` has build instructions for windows, although would require that you clone and build raylib in the `../raylib` directory relative to the one that has the Makefile.

`CMakeLists.txt` has build instructions and requires at least `Version 3.25` of [`cmake`](https://cmake.org) is installed, using cmake, you do need to worry about building the raylib library yourselves.

`build.sh` works on Linux and will either use `cmake` (if present) or would require `git`, `gcc` and `make` are installed, It takes care of cloning and building raylib for you so all you have to do is is call the script, do make sure that at least `cmake` or `git` and `gcc` and `make` are installed.

Build instructions on Windows:

Requires `make` and `gcc`


You can get `gcc` and `make` from [Winlibs](https://winlibs.com/) or [W64devkit](https://github.com/skeeto/w64devkit)

`make`


Do note that Winlibs includes `make` but the executable is named `mingw32-make`, so the build instruction would be as follows

`mingw32-make`

Alternatively you can install `cmake` and just execute the `build.bat` from the command line

`./build.bat`

Build instructions for Linux:


You might want to install `git`, `gcc` and `make` from your package manager and then execute `build.sh`

`./build.sh`

Alternatively install `cmake` from your package manager and then execute `build.sh`

`./build.sh`