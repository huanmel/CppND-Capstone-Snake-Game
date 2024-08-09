#include "snake.h"
#include <cmath>
#include <iostream>
#include <string>
#include "food.h"
using namespace std;

Food::Food(int grid_width, int grid_height)
    : Body2(0, 0),
      _engine(_dev()),
      _random_w(0, static_cast<int>(grid_width - 1)),
      _random_h(0, static_cast<int>(grid_height - 1)),
      _random_q(1, static_cast<int>(3)),
      _q(FoodQual::fMed)

{
    // _x = 0;
    // _y = 0;
};

void Food::placeFood(Snake const &snake)
{

    int x, y, q;
    // q = _random_q(_engine);
    // _q = static_cast<Food::FoodQual>(q);
    while (true)
    {
        x = _random_w(_engine);
        y = _random_h(_engine);

        // Check that the location is not occupied by a snake item before placing
        // food.
        if (!snake.SnakeCell(x, y))
        {
            // _x = x;
            // _y = y;
            // _cell = std::make_unique<Cell>(x, y);
            //  _mutex.lock();
            std::unique_ptr<Cell> _cell1 = std::make_unique<Cell>(x, y, 1);
            _food.push_back(std::move(_cell1));
            std::cout << "food placed" << std::endl;
            //  _mutex.unlock();
            // _fd.placeFood(x,y);
            return;
        }
    }
}
void Food::myfun()
{
    // _mutex.lock();
    std::lock_guard<std::mutex> lck(_mutex);
    try
    {

        std::cout << "my fun started" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(3000)); // simulate work
        std::cout << "my fun finished" << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "err" << std::endl;
        std::cout << e.what() << std::endl;
        return;
    }
    // _mutex.unlock();
}
void Food::generateFood(std::shared_ptr<Food> food)
{
    std::unique_lock<std::mutex> lck(_mutex);
    //  std::cout << "Vehicle #" << _id << "::drive: thread id = " << std::this_thread::get_id() << std::endl;
    lck.unlock();
    auto start_time = std::chrono::high_resolution_clock::now();
    // Create a random number generator engine
    std::random_device rd;
    std::mt19937 gen(rd());
    // Create a distribution for the desired range
    std::uniform_real_distribution<> dist(4, 10);
    double randomNumber = dist(gen);
    while (true)
    {

        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
        // Cast seconds to double
        double durationSecondsDouble = static_cast<double>(duration.count());
        if (durationSecondsDouble > randomNumber)
        {
            // toggle
            _q = (_q == FoodQual::fHi) ? FoodQual::fLow : FoodQual::fHi;

            // TODO  сcheck sends an update method to the message queue using move semantics
            // FoodQual currentPhase = _q;
            // Cell c;

            // _msgQ_TrLightPh.send(std::move(c));
            int x = _random_w(_engine);
            int y = _random_h(_engine);

            std::unique_ptr<Cell> _cell1 = std::make_unique<Cell>(x, y);
            _food.push_back(std::move(_cell1));

            std::unique_ptr<Cell> _cell2 = std::make_unique<Cell>(x, y);
            food->_food.push_back(std::move(_cell2));

            start_time = std::chrono::high_resolution_clock::now();
            randomNumber = dist(gen);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    };
}

void Food::simulate(std::shared_ptr<Food> food)
{
    threads.emplace_back(std::thread(&Food::generateFood, this, food));
}

void Food::waitForFood()
{
    // while (true)
    // {
    //     Cell c = _msgQ_TrLightPh.receive();

    //     // if (currentPhase == TrafficLightPhase::green)
    //     // {
    //     break;
    //     // }
    // }
}

void Food::cleanFood()
{
    std::unique_lock<std::mutex> lck(_mutex);
    //  std::cout << "Vehicle #" << _id << "::drive: thread id = " << std::this_thread::get_id() << std::endl;
    lck.unlock();
    auto start_time = std::chrono::high_resolution_clock::now();
    // Create a random number generator engine
    std::random_device rd;
    std::mt19937 gen(rd());
    // Create a distribution for the desired range
    std::uniform_real_distribution<> dist(3, 7);
    double randomNumber = dist(gen);
    while (true)
    {

        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
        // Cast seconds to double
        double durationSecondsDouble = static_cast<double>(duration.count());
        if (durationSecondsDouble > randomNumber)
        {

            // int x = _random_w(_engine);
            // int y = _random_h(_engine);
            // int q = _random_q(_engine);

            // std::unique_ptr<Cell> _cell1 = std::make_unique<Cell>(x, y);
            // _food.push_back(std::move(_cell1));

            // std::unique_ptr<Cell> _cell2 = std::make_unique<Cell>(x, y, q);
            if (getFoodSize() > 1)
            {
                lck.lock();
                // food->_food.push_back(std::move(_cell2));
                _food.erase(_food.begin());
                lck.unlock();
            }
            start_time = std::chrono::high_resolution_clock::now();
            randomNumber = dist(gen);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    };
};

FoodGen::FoodGen(int grid_width, int grid_height) : _engine(_dev()),
                                                _random_w(0, static_cast<int>(grid_width - 1)),
                                                _random_h(0, static_cast<int>(grid_height - 1)),
                                                _random_q(1, static_cast<int>(3))
{
}

void FoodGen::generateFood(std::shared_ptr<Food> food)
{
    //  std::unique_lock<std::mutex> lck(_mutex);
    std::unique_lock<std::mutex> lck(food->_mutex);
    //  std::cout << "Vehicle #" << _id << "::drive: thread id = " << std::this_thread::get_id() << std::endl;
    lck.unlock();
    auto start_time = std::chrono::high_resolution_clock::now();
    // Create a random number generator engine
    std::random_device rd;
    std::mt19937 gen(rd());
    // Create a distribution for the desired range
    std::uniform_real_distribution<> dist(4, 10);
    double randomNumber = dist(gen);
    while (true)
    {

        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
        // Cast seconds to double
        double durationSecondsDouble = static_cast<double>(duration.count());
        if (durationSecondsDouble > randomNumber)
        {

            int x = _random_w(_engine);
            int y = _random_h(_engine);
            int q = _random_q(_engine);

            // std::unique_ptr<Cell> _cell1 = std::make_unique<Cell>(x, y);
            // _food.push_back(std::move(_cell1));

            std::unique_ptr<Cell> _cell2 = std::make_unique<Cell>(x, y, q);
            lck.lock();
            food->_food.push_back(std::move(_cell2));
            lck.unlock();
            start_time = std::chrono::high_resolution_clock::now();
            randomNumber = dist(gen);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    };
}
// int const Food::getX(){return _x;};
