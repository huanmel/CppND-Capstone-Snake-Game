#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"
#include <vector>
#include <regex>
#include <fstream>
using namespace std;

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const
{
  if (snake.direction != opposite || snake.size == 1)
    snake.direction = input;
  return;
}

void Controller::HandleInput(GameInterface& game, bool &running, Snake &snake, Renderer &render) const
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
       case SDLK_k:
        ChangeDirection(snake, Snake::Direction::kUp,
                        Snake::Direction::kDown);
        break;

      case SDLK_DOWN:
      case SDLK_j:
        ChangeDirection(snake, Snake::Direction::kDown,
                        Snake::Direction::kUp);
        break;

      case SDLK_LEFT:
       case SDLK_h:
        ChangeDirection(snake, Snake::Direction::kLeft,
                        Snake::Direction::kRight);
        break;

      case SDLK_RIGHT:
       case SDLK_l:
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
        SDL_StartTextInput();

        std::string userInput = "";
        while (!done)
        {
          render.RenderText(userInput);
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
              if (e1.key.keysym.sym == SDLK_BACKSPACE && userInput.size())
              {
                userInput.pop_back();
                // std::cout << "Text entered: " << userInput << std::endl;
              }
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
        // break;
        // SDL_StopTextInput();
        if (!userInput.empty())
        {
          userInput = userInput + " ";
          std::string cmd_w = "w";
          std::string cmd_r = "r";
          std::string cmd_q = "q";
          vector<string> userString;
          std::string word = "";
          // Defining a regular expression.
          std::regex r("\\s+");
          for (auto x : userInput)
          {
            if (x == ' ')
            {
              // std::cout << word << std::endl;

              // Using the regular expression to remove whitespaces.
              word = std::regex_replace(word, r, "");
              userString.push_back(word);
              word = "";
            }
            else
            {
              word = word + x;
            }
          }
          // std::cout << word << std::endl;
          for (auto x : userString)
          {
            cout << x << endl;
          }
          string cmd = userString[0];
          string cmd_arg = "";
          if (userString.size() > 1)
          {
            cmd_arg = userString[1];
          };
          if (cmd_arg.compare("")==0)
          {
            // set default file name to write read
            cmd_arg="saved_game.txt";
          }
          if (cmd.compare(cmd_w) == 0)
          {
            cout << "write to file: " << cmd_arg << endl;
            ofstream file1;
            // file1.open("Employee.txt", ios::app);
            // file1.write((char *)&snake, sizeof(snake));
            // file1.close();
            game.Save(cmd_arg);
            
            //       ofstream fout("saved_point.txt");
            // fout << snake.head_x << ' ' << snake.head_y<<'\n';
            // fout << snake.head_x << ' ' << snake.head_y;
            // fout.close();
      
          }
          else if (cmd.compare(cmd_r) == 0)
          {
            game.Load(cmd_arg);
            // cout << "read from file: " << cmd_arg << endl;
            // ifstream fin("saved_point.txt");
            // fin >> snake.head_x >> snake.head_y;
            // fin.close();
            // // ifstream file2;
            // // file2.open("Employee.txt", ios::in);
            // // file2.seekg(0);
            // // // Snake snake2;
            // // file2.read((char *)&snake, sizeof(snake));
            // printf("\nalive :%d", snake.alive);
            // printf("\nsize:%d", snake.size);
            // printf("\nspeed:%f", snake.speed);
            // printf("\nhead_x:%f", snake.head_x);
            // printf("\nhead_y:%f", snake.head_y);
            // file2.close();
          }
          else if (cmd.compare(cmd_q) == 0)
          {
            cout << "quit from the program " << endl;
            std::exit(0);
          }
          else
          {
            cout << "no cmd " << endl;
          }
        }
      }
    }
  }
}