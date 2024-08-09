// #include "snake.h"
#include <cmath>
#include <iostream>
#include <string>
// #include "Cell.h"
#include "cell.h"
using namespace std;
Cell::Cell()
{
    _x = 0;
    _y = 0;
}

Cell::Cell(int x, int y)
{
    _x = x;
    _y = y;
}
Cell::Cell(int x, int y, int q)
{
    _x = x;
    _y = y;
    _q = static_cast<Cell::CellQ>(q);
}
Cell::Cell(SDL_Point p)
{
    _x = p.x;
    _y = p.y;
}

Cell::~Cell()
{
    std::cout << "DELETING instance of Cell at " << this << std::endl;
}

