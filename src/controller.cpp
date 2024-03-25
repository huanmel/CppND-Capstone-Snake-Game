#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const
{
  if (snake.direction != opposite || snake.size == 1)
    snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Snake &snake) const
{
  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      running = false;
    }
    else if (e.type == SDL_KEYDOWN)
    {
      std::cout << "user input:" << e.key.keysym.sym << "\n";
      switch (e.key.keysym.sym)
      {
      case SDLK_UP:
        ChangeDirection(snake, Snake::Direction::kUp,
                        Snake::Direction::kDown);
        break;

      case SDLK_DOWN:
        ChangeDirection(snake, Snake::Direction::kDown,
                        Snake::Direction::kUp);
        break;

      case SDLK_LEFT:
        ChangeDirection(snake, Snake::Direction::kLeft,
                        Snake::Direction::kRight);
        break;

      case SDLK_RIGHT:
        ChangeDirection(snake, Snake::Direction::kRight,
                        Snake::Direction::kLeft);
        break;
        /*     case SDLK_COLON:
              // pause the game and get user input
              std::cout << "user input :\n";
              SDL_Event textEvent;
              SDL_WaitEvent(&textEvent); // Pa
              break; */
      }
    }
    else if (e.type == SDL_TEXTINPUT)
    {
      switch (e.text.text[0])
      {
      case SDLK_COLON:
        char *text;
        char *composition;
        Sint32 cursor;
        Sint32 selection_len;
        // pause the game and get user input
        std::cout << "user input :\n";
        // SDL_Event textEvent;
        // SDL_WaitEvent(&textEvent); // Pa
        SDL_bool done = SDL_FALSE;
        // SDL_StartTextInput();

        std::string userInput = "";
        while (!done)
        {
          SDL_Event e1;
          if (SDL_PollEvent(&e1))
          {
            switch (e1.type)
            {
            case SDL_QUIT:

              // Quit
              std::cout << "Text entered: " << userInput << std::endl;

              done = SDL_TRUE;
            case SDL_KEYDOWN:
              if (e1.key.keysym.sym == SDLK_RETURN)
              {
                // Quit
                // std::cout << "Text entered: " << event.text.text << std::endl;
                std::cout << "Text entered: " << userInput << std::endl;

                done = SDL_TRUE;
              }
              break;
            case SDL_TEXTINPUT:
              // Add new text onto the end of our text
              // strcat(text, event.text.text);
              userInput += e1.text.text;
              break;
            case SDL_TEXTEDITING:
              // Update the composition text.
              // Update the cursor position.
              // Update the selection length (if any).
              // composition = event.edit.text;
              // cursor = event.edit.start;
              // selection_len = event.edit.length;
              break;
            }
          }
        }
        break;
      }
      // SDL_StopTextInput();
    }
  }
}