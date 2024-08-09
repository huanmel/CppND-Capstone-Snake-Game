#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include <vector>
#include "SDL.h"
#include <string>
#include <random>
#include "snake.h"
// #include "body.h"
#include "body2.h"
#include "cell.h"
#include <memory>
#include <thread>
#include "mesq.h"
#include <mutex>
#include <deque>
#include <condition_variable>
using namespace std;

// Forward declaration
class Body2;

class Food : public Body2, public std::enable_shared_from_this<Food>
{
public:
    enum class FoodQual
    {
        fLow = 1,
        fMed = 2,
        fHi = 3
    };

    Food(int grid_width, int grid_height);
    void placeFood(Snake const &snake);
    void myfun();
    void operator()()
    {
        std::cout << " object has been created \n"
                  << std::endl;
    }
    FoodQual getQ() const { return _q; };


    // std::unique_ptr<Cell> _cell;
    std::vector<std::unique_ptr<Cell>> _food;
    int getFoodSize() const { return _food.size(); };

    int getX(int i) const
    {
        return _food[i]->getX();
    };

    int getY(int i) const
    {
        return _food[i]->getY();
    };

    Cell::CellQ getQ(int i) const
    {
        return _food[i]->getQ();
    };



    void generateFood(std::shared_ptr<Food> food);
    void simulate(std::shared_ptr<Food> food);
    std::shared_ptr<Food> get_shared_this() { return shared_from_this(); }
    void waitForFood();
    void cleanFood();
    std::mutex _mutex;

private:
    FoodQual _q;

    std::random_device _dev;
    std::mt19937 _engine;
    std::uniform_int_distribution<int> _random_q;
    std::uniform_int_distribution<int> _random_w;
    std::uniform_int_distribution<int> _random_h;

    std::vector<std::thread> threads; // holds all threads that have been launched within this object
    // MessageQueue<Cell> _msgQ;
    // std::condition_variable _condition;
};

class FoodGen
{
public:
    FoodGen(int grid_width, int grid_height);
    void generateFood(std::shared_ptr<Food> food);
private:
    std::random_device _dev;
    std::mt19937 _engine;
    std::uniform_int_distribution<int> _random_q;
    std::uniform_int_distribution<int> _random_w;
    std::uniform_int_distribution<int> _random_h;
    std::mutex _mutex;
};

#endif