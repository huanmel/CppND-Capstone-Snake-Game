#ifndef BODY2_H
#define BODY2_H

#include <vector>
#include "SDL.h"
#include <string>
#include <random>
// #include "snake.h"
#include <memory>
#include "cell.h"

using namespace std;

class Body2
{
public:
    Body2();
    Body2(int x, int y);

    ~Body2(); // 1 : destructor
    void updateCell(std::unique_ptr<Cell> source);
    bool updateBody(SDL_Point &current_cell);

    std::vector<std::unique_ptr<Cell>> _bodyC;

    int getX() const
    // get heads x
    {
        return _bodyC[0]->getX();
    };

    int getX(int i) const
    {
        return _bodyC[i]->getX();
    };

    int getY() const
    // get heads y
    {
        return _bodyC[0]->getY();
    };

    int getY(int i) const
    {
        return _bodyC[i]->getY();
    };

    void setX(int x) { _bodyC[0]->setX(x); };
    void setY(int y) { _bodyC[0]->setY(y); };

    void setX(int i, int x) { _bodyC[i]->setX(x); };
    void setY(int i, int y) { _bodyC[i]->setY(y); };
    void clear(){_bodyC.clear();};

    int getBodySize() const
    {
        return _bodyC.size();
    };

    bool getIsInBody(int x, int y) const;

protected:
};

#endif