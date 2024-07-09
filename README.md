# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

In this project, I have added [new features](#New Features) such as using A* search to enable the Snake to calculate paths and automatically move towards food. Additionally, I have optimized mechanisms by utilizing references, semantic moves, and selecting more  appropriate data structures to improve algorithm performance. Finally, I revised the program into a multithreaded version, whichseparated the program logic clearly, and implemented synchronization mechanisms to prevent race conditions. See [Rubric Points](#Rubric Points)

## New Features
* Pause
  * Press `p` to pause or resume the game.
* Record the Highest Score
  * Display the highest score at the end of the game.
* Auto Navigation
  * Press `s` to switch between manual mode and auto navigation mode.
  * The snake will search for the path using the A* Search algorithm and automatically change direction according to the path.
  * The game will end if no feasible path can be found.

## Rubric Points

Searching for the keyword [FP.xx] int the project allows one to find the corresponding code.

**1. Loops, Functions, I/O**
* [FP.1a] The project demonstrates an understanding of C++ functions and control structures.
* [FP.1b] The project reads data from a file and process the data, or the program writes data to a file.
* [FP.1c]The project accepts user input and processes the input.

**2. Object Oriented Programming**
* [FP.2a] One or more classes are added to the project with appropriate access specifiers for class members.
* [FP.2b] Class constructors utilize member initialization lists.
* [FP.2c] Classes abstract implementation details from their interfaces.

**3. Memory Management**
* [FP.3a] The project makes use of references in function declarations.
* [FP.3b] The project uses destructors appropriately.
* [FP.3c] The project uses move semantics to move data instead of copying it, where possible.
* [FP.3d] The project uses smart pointers instead of raw pointers.

**4. Concurrency**
* [FP.4a] The project uses multithreading.
* [FP.4b] A mutex or lock is used in the project.

**5. Optimalization**
* [FP.5a] Using a different data structure to reduce time complexity

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.