#include "snake.h"
#include <cmath>
#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Body2;
Snake::Snake(int grid_width_in, int grid_height_in)
    : _body2{Body2(0, 0)}
{
  // _body2 = Body2(0, 0);
  grid_width = grid_width_in;
  grid_height = grid_height_in,
  head_x = grid_width / 2;
  head_y = grid_height / 2;

  // create head as the first cell in the snake body
  // std::unique_ptr<Cell> c = std::make_unique<Cell>(static_cast<int>(head_x), static_cast<int>(head_y));
  // _body2.updateCell(std::move(c));
  _body2.setX(static_cast<int>(head_x));
  _body2.setY(static_cast<int>(head_y));
  // _body2 = Body2(static_cast<int>(head_x), static_cast<int>(head_y));

  // _body=
  // std::unique_ptr<SDL_Point> p = std::make_unique<SDL_Point>(0,0);
  // Body p(0, 0);
  // std::unique_ptr<Body> ptr2x(p);
  // std::unique_ptr<Body> p = std::make_unique<Body>(0, 0);
  // std::unique_ptr<Body> _body = std::make_unique<Body>(0, 0);
  // _body.emplace_back(std::move(p));
  //  _body.push_back(std::make_unique<Body>(0,0));
}

Snake::~Snake()
{
}

// Snake::Snake(const Snake &source)
// {
// }

// Snake &Snake::operator=(const Snake &source)
// {
//     // TODO: insert return statement here
//     return *this;
// }

// Snake::Snake(Snake &&source)
// {
// }

// Snake &Snake::operator=(Snake &&source)
// {
//   // TODO: insert return statement here
//   return *this;
// }

void Snake::Update()
{
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)}; // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)}; // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  alive = _body2.updateBody(current_cell);

  // if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y)
  // {
  //   UpdateBody(current_cell, prev_cell);
  // }
}

void Snake::Str2Dir(std::string dir_s)
{
  Snake::Direction dir = Direction::kUp;

  if (dir_s.compare("kUp") == 0)
  {
    dir = Direction::kUp;
    /* code */
  }
  else if (dir_s.compare("kDown") == 0)
  {
    dir = Direction::kDown;
  }
  else if (dir_s.compare("kLeft") == 0)
  {
    dir = Direction::kLeft;
  }
  else if (dir_s.compare("kRight") == 0)
  {
    dir = Direction::kRight;
  }
  direction = dir;
}

std::string Snake::Dir2Str()
{
  std::string dir_s = "";
  switch (direction)
  {
  case Direction::kUp:
    /* code */
    dir_s = "kUp";
    break;
  case Direction::kDown:
    /* code */
    dir_s = "kDown";
    break;
  case Direction::kLeft:
    /* code */
    dir_s = "kLeft";
    break;
  case Direction::kRight:
    /* code */
    dir_s = "kRight";
    break;

  default:
    break;
  }
  cout << dir_s << endl;
  return dir_s;
}

void Snake::speedUpdate()
{
  speed += 0.02;
  float avgSpeed = 0;
  Cell::CellQ  Q;
  for (unsigned int i = 0; i < _body2.getBodySize(); i++)
  {
    // Q =  static_cast<int>(_body2.getQ(i));
    // Q =(_body2->getQ(i));
  }
}

void Snake::UpdateHead()
{
  switch (direction)
  {
  case Direction::kUp:
    head_y -= speed;
    break;

  case Direction::kDown:
    head_y += speed;
    break;

  case Direction::kLeft:
    head_x -= speed;
    break;

  case Direction::kRight:
    head_x += speed;
    break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

// void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell)
// {
//   // Add previous head location to vector
//   // body.push_back(prev_head_cell);
//   body2.push_back(Body(prev_head_cell));

//   if (!growing)
//   {
//     // Remove the tail from the vector.
//     // body.erase(body.begin());
//     body2.erase(body2.begin());
//   }
//   else
//   {
//     growing = false;
//     size++;
//   }

//   // Check if the snake has died.
//   for (auto const &item : body)
//   {
//     if (current_head_cell.x == item.x && current_head_cell.y == item.y)
//     {
//       alive = false;
//     }
//   }
// }

void Snake::GrowBody()
{
  growing = true;
}

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) const
{
  return _body2.getIsInBody(x, y);
}