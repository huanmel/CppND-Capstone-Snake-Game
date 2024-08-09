#ifndef CELL_H
#define CELL_H

#include "SDL.h"
#include <string>
#include <random>
#include <vector>
#include <thread>
#include <mutex>
#include <deque>
#include <condition_variable>
// #include "snake.h"
using namespace std;

class Cell
{
public:
    enum class CellQ
    {
        fLo = 1,
        fMe = 2,
        fHi = 3
    };

    Cell();
    Cell(int x, int y);
    Cell(int x, int y, int q);
    Cell(SDL_Point p);
    ~Cell(); // 1 : destructor

    int getX() const
    {
        return _x;
    };
    int getY() const { return _y; };
    CellQ getQ() const { return _q; };
    void setX(int x) { _x = x; };
    void setY(int y) { _y = y; };

protected:
    int _x;
    int _y;
    CellQ _q;
};

#endif