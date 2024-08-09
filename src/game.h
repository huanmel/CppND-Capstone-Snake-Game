#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "GameInterface.h"
#include <iostream>
#include <fstream>
#include "food.h"

#include <memory>
#include <thread>
#include <future>
#include <algorithm>
// Forward declaration 
class Controller;
class GameInterface;

class Game : public GameInterface
{
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  // Game(std::size_t grid_width, std::size_t grid_height,Controller const &&controller, Renderer const &&render);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  std::shared_ptr<Food> _food;
  std::vector<std::shared_ptr<FoodGen>> FoodGens;
  std::vector<std::thread> threads; // holds all threads that have been launched within this object


  // Renderer _rndr;
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  void Save(std::string filename) override;
  void Load(std::string filename) override;
  // int SaveGame(std::string filename);
  // int LoadGame(std::string filename);

  // void PlaceFood();
  void Update();
};

#endif