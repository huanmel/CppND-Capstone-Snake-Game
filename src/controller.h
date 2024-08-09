#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "renderer.h"
#include "game.h"
// Forward declaration of the Controller class
class Game;
// Forward declaration of the Game class
class GameInterface;

class Controller {
 public:
  void HandleInput(GameInterface& game,bool &running, Snake &snake, Renderer &render) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif