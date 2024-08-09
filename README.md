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



## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
