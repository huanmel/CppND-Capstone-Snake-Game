// #include "snake.h"

#include <cmath>
#include <iostream>
#include <string>
#include "body2.h"
using namespace std;

Body2::Body2()
{

}
Body2::Body2(int x, int y)
{
    std::unique_ptr<Cell> c = std::make_unique<Cell>(x, y);
    updateCell(std::move(c));
}


Body2::~Body2()
{
    std::cout << "DELETING instance of Body2 at " << this << std::endl;
}

void Body2::updateCell(std::unique_ptr<Cell> source)
{
    _bodyC.push_back(std::move(source));
}

bool Body2::updateBody(SDL_Point &current_cell)
// return alive status
{
    bool isAlive = true;
    if (current_cell.x != getX() || current_cell.y != getY())
    {

        int x1, y1, x2, y2;

        unsigned int vecSize = getBodySize();

        x1 = getX();
        y1 = getY();
        setX(current_cell.x);
        setY(current_cell.y);
        if (vecSize > 1)
        {
            for (unsigned int i = 1; i < vecSize; i++)
            {
                x2 = getX(i);
                y2 = getY(i);
                setX(i, x1);
                setY(i, y1);
                x1 = x2;
                y1 = y2;
                if (current_cell.x == x1 && current_cell.y == y1)
                {
                    isAlive = false;
                }
            }
        }
    }
    return isAlive;
}

bool Body2::getIsInBody(int x, int y) const
{

    for (unsigned int i = 0; i < getBodySize(); i++)
    {
        if (x == getX(i) && y == getY(i))
        {
            return true;
        }
    }
    return false;
}
