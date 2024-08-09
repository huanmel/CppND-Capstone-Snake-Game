#include "game.h"
#include <iostream>
#include <fstream>
#include "SDL.h"
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
using namespace std;

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1))
// _fd(grid_width, grid_height)
{

  _food = std::make_shared<Food>(grid_width, grid_height);
  _food->placeFood(snake);
  int nfoods = 3;

  threads.emplace_back(std::thread(&Food::cleanFood, _food));
  for (size_t nv = 0; nv < nfoods; nv++)
  {
    FoodGens.push_back(std::make_shared<FoodGen>(grid_width, grid_height));
  }

  for (size_t nv = 0; nv < nfoods; nv++)
  {
    threads.emplace_back(std::thread(&FoodGen::generateFood, FoodGens[nv], _food));
  }

}

void Game::Save(std::string filename)
{
  // Logic to save the game
  ofstream fout(filename);
  fout << score << '\n';
  // fout << food.x << ' ' << food.y << '\n';
  // fout << _fd.getX() << ' ' << _fd.getY() << '\n';

  fout << static_cast<int>(snake.head_x) << ' ' << static_cast<int>(snake.head_y) << ' ' << snake.size << ' ' << snake.speed << ' ' << snake.Dir2Str() << '\n';
  fout << snake._body2.getBodySize() << '\n';

  for (unsigned int i = 0; i < snake._body2.getBodySize(); i++)
  {
    fout << snake._body2.getX(i) << ' ' << snake._body2.getY(i) << '\n';
  }
  fout.close();
  std::cout << "Game is being saved..." << filename << std::endl;
}

void Game::Load(std::string filename)
{
  cout << "read from file: " << filename << endl;
  ifstream fin(filename);
  string line;

  getline(fin, line);
  std::istringstream iss1(line);
  iss1 >> score;

  getline(fin, line);
  iss1.str(line);
  iss1.clear();

  string dir_s;
  dir_s = iss1.str();
  iss1 >> snake.head_x >> snake.head_y >> snake.size >> snake.speed >> dir_s;
  snake.Str2Dir(dir_s);
  snake.alive=true;

  getline(fin, line);
  iss1.str(line);
  iss1.clear();
  int sz;
  iss1 >> sz;

  if (sz > 0)
    // snake.body.clear();
  snake._body2.clear();
  // load body
  int x,y;
  {
    for (int i = 0; i < sz; i++)
    {
      SDL_Point point;
      getline(fin, line);
      iss1.str(line);
      iss1.clear();
      iss1 >> x >> y;
      std::unique_ptr<Cell> C = std::make_unique<Cell>(static_cast<int>(x), static_cast<int>(y));
      snake._body2.updateCell(std::move(C));
      // snake.body.push_back(point);
      // snake.body2.push_back(point);
    }
  }

  fin.close();
  // ifstream file2;
  // file2.open("Employee.txt", ios::in);
  // file2.seekg(0);
  // // Snake snake2;
  // file2.read((char *)&snake, sizeof(snake));
  printf("\nalive :%d", snake.alive);
  printf("\nsize:%d", snake.size);
  printf("\nspeed:%f", snake.speed);
  printf("\nhead_x:%f", snake.head_x);
  printf("\nhead_y:%f", snake.head_y);
  std::cout << "\nGame is being loaded...\n"
            << filename << std::endl;
  // renderer.Render(snake, food);
  // Logic to save the game
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 food_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running)
  {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(*this, running, snake, renderer);
    Update();
    renderer.Render(snake, _food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000)
    {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

// void Game::PlaceFood()
// {
//   int x, y, q;
//   while (true)
//   {
//     x = random_w(engine);
//     y = random_h(engine);
//     // Check that the location is not occupied by a snake item before placing
//     // food.
//     if (!snake.SnakeCell(x, y))
//     {
//       food.x = x;
//       food.y = y;
//       // _fd.placeFood(x,y);
//       return;
//     }
//   }
// }

void Game::Update()
{
  if (!snake.alive)
    return;

  snake.Update();


  int vecSize = _food->getFoodSize();
  if (vecSize > 0)
  {
    for (unsigned int i = 0; i < vecSize; i++)
    {
      if (_food->getX(i) == snake._body2.getX() && _food->getY(i) == snake._body2.getY())
      {

        snake._body2.updateCell(std::move(_food->_food[i]));
        _food->_food.erase(_food->_food.begin() + i);
        score++;
        // PlaceFood();
        // _food->placeFood(snake);
        // Grow snake and increase speed.
        // snake.GrowBody();
        // snake.speed += 0.02;
        snake.speedUpdate();
        break;
      }
    }
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake._body2.getBodySize(); }