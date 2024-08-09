#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include <string>
#include "body2.h"

using namespace std;

class Snake
{
public:
  enum class Direction
  {
    kUp,
    kDown,
    kLeft,
    kRight
  };

  Snake(int grid_width, int grid_height);
  ~Snake(); // 1 : destructor
  // Snake(const Snake &source); // 2 : copy constructor
  // Snake &operator=(const Snake &source); // 3 : copy assignment operator
  // Snake(Snake &&source);                 // 4 : move constructor
  // Snake &operator=(Snake &&source); // 5 : move assignment operator

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y) const;
  std::string Dir2Str();
  void Str2Dir(std::string dir_s);
  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  // std::vector<SDL_Point> body;
  // std::vector<Body> body2;
  Body2 _body2;
  void speedUpdate();

private:
  void UpdateHead();
  // void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  // std::unique_ptr<Body> _body;
  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif