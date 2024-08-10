# CPPND: Capstone Snake Game Example. Snake VIM

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

## how to control
There's analog of vim menu to get access to quit, write and load game progress. At first during game you need to press ":" button to get access to command line.
It would looks like below. After you need to write one of the command.
<img src="assets\game_menu.png"/>

### menu command
Exit Commands

:q Quit (a warning is printed if a modified file has not been saved)

### File Manipulation Commands

:w Write workspace to default file (save progress to the same file)

:w file_name Write workspace to named file (save progress to new file_name)

:r read game progress from the default file

:r file_name Read contents of a file to the workspace (load progress)

### Move snake commands
Button below could be used during game to control snake direction movement. Its analog of VIM cursor control. 

	h - move cursor left
	j - move cursor down
	k - move cursor up
	l - move cursor right

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

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
3. install additional libraries:
	* sudo apt install libsdl2-image-dev
	* sudo apt-get install libsdl2-ttf-dev
	also this resource already used 
    https://github.com/aminosbh/sdl2-cmake-modules
4. Compile: `cmake .. && make`
5. Run it: `./MySnakeSDL`.

# Features added to the project
## Loops, Functions, I/O 
| CRITERIA                                                                                       | MEETS SPECIFICATIONS                                                                                                     | TODO                                                                                                                      | STATUS |
| ---------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------ | ------------------------------------------------------------------------------------------------------------------------- | ------ |
| The project demonstrates an understanding of C++ functions and control structures.             | A variety of control structures are added to the project.<br><br>The project code is clearly organized into functions.   | Code is separated into classed, some helper functions added like to write, load or translate snakes direction to string   | DONE   |
| The project reads data from a file and process the data, or the program writes data to a file. | The project reads data from an external file or writes data to a file as part of the necessary operation of the program. | add read write the progress to the file                                                                                   | DONE   |
| The project accepts user input and processes the input.                                        | In addition to controlling the snake, the game can also receive new types of input from the player.                      | vim mode <br>:w :s - save game<br>:q - quit<br>:l - load<br>:r - reload<br>:s - screenshot<br>hjkl - to control the snake | DONE   |
| The project uses data structures and immutable variables.                                      | The project uses arrays or vectors **and** uses constant variables.                                                      | Body and food are done as vector                                                                                          | DONE   |

## Object Oriented Programming
| CRITERIA                                                                                           | MEETS SPECIFICATIONS                                                                                                                                                                                                                                                                  | TODO                                                                                                                                                                                                                                                                                                                                                                                                   | STATUS |
| -------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ------ |
| One or more classes are added to the project with appropriate access specifiers for class members. | Classes are organized with attributes to hold data and methods to perform tasks.<br><br>All class data members are explicitly specified as public, protected, or private.<br><br>Member data that is subject to an invariant is hidden from the user and accessed via member methods. | GameInterface class  to control save and load game progress  added . Methods are pure virtual that are implemented in game class. <br>Also added classes:<br>* Cell - basic class for foods and body<br>* Body2 - use cell class as the main construction in vector and add some methods to control it<br>* Food - inherit Body2, used to represent food<br>* FoodGen  - used to generate food<br><br> | DONE   |
| Class constructors utilize member initialization lists.                                            | All class members that are set to argument values are initialized through member initialization lists.                                                                                                                                                                                | Init class instancs  food and snakes body                                                                                                                                                                                                                                                                                                                                                              | DONE   |
| Classes abstract implementation details from their interfaces.                                     | All class member functions document their effects, either through function names, comments, or formal documentation.<br><br>Member functions do not change the program state in undocumented ways.                                                                                    | <br>                                                                                                                                                                                                                                                                                                                                                                                                   |        |
| Overloaded functions allow the same function to operate on different parameters.                   | One function is overloaded with different signatures for the same function name.                                                                                                                                                                                                      | Body2 getX getY setX setY could be called with different arguments                                                                                                                                                                                                                                                                                                                                     | DONE   |
| Classes follow an appropriate inheritance hierarchy with virtual and override functions.           | Inheritance hierarchies are logical. One member function in an inherited class overrides a virtual base class member function.                                                                                                                                                        | game interface is inherited in game class, body is inherited in food                                                                                                                                                                                                                                                                                                                                   | DONE   |
| Templates generalize functions or classes in the project.                                          | One function or class is declared with a template that allows it to accept a generic parameter.                                                                                                                                                                                       |                                                                                                                                                                                                                                                                                                                                                                                                        |        |

## Memory Management 

| CRITERIA                                                                                  | MEETS SPECIFICATIONS                                                                                                                                                                                                                     | TODO                                                                                                                                                                                                                          | STATUS |
| ----------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------ |
| The project makes use of references in function declarations.                             | At least two variables are defined as references, or two functions use pass-by-reference in the project code.                                                                                                                            | placeFood use snake as const reference argument                                                                                                                                                                               | DONE   |
| The project uses destructors appropriately.                                               | At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor.                                                     | add destructor in the object of classes like cell, food                                                                                                                                                                       | DONE   |
| The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate. | The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction. |                                                                                                                                                                                                                               |        |
| The project follows the Rule of 5.                                                        | For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.                                          |                                                                                                                                                                                                                               |        |
| The project uses move semantics to move data instead of copying it, where possible.       | The project relies on the move semantics, instead of copying the object.                                                                                                                                                                 | Used body2, food and cell, see method updateCell as example. <br><br>Idea here is that created once cell is then moved between different objects that own it. For example cell is part of the food until it is eaten by snake | done   |
| The project uses smart pointers instead of raw pointers.                                  | The project uses at least one smart pointer: `unique_ptr`, `shared_ptr`, or `weak_ptr`.                                                                                                                                                  | Used in the food, where cells  are stored as resources                                                                                                                                                                        | done   |

## Concurrency - Meet at Least 2 Criteria

| MEETS SPECIFICATIONS                                                                                                                              | CRITERIA                                     | TODO                                                                                                                                                                                                                                        | STATUS |
| ------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------ |
| The project uses multiple threads or async tasks in the execution.                                                                                | The project uses multithreading.             | Each food generator  item exist in its own thread with function to generate food from time to time in random way. Also there is a separate thread with function that will clean created food from time to time so the food could disappear. | done   |
| A promise and future is used to pass data from a worker thread to a parent thread in the project code.                                            | A promise and future is used in the project. |                                                                                                                                                                                                                                             |        |
| A mutex or lock (e.g. `std::lock_guard` or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code. | A mutex or lock is used in the project.      | food generators and food cleaner use one resource that is locked at the moment of access and possible  manipulation                                                                                                                         | done   |
| A `std::condition_variable` is used in the project code to synchronize thread execution.<br>                                                      | A condition variable is used in the project. |                                                                                                                                                                                                                                             |        |
## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
