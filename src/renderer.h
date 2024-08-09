#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "food.h"
// #include "body.h"
#include "body2.h"
#include <stdint.h>
#include <tuple>
#include <SDL_pixels.h>

#define FONT_PATH   "assets/Roboto-Regular.ttf"
#define IMG_PATH   "assets/game_menu.png"
// #define IMG_PATH   "assets/test.png"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const  &snake, std::shared_ptr<Food> fd1);
  void UpdateWindowTitle(int score, int fps);
  void RenderText(const std::string input);
  // typedef struct
  // {
  //   uint8_t R=0x00;
  //   uint8_t G=0x00;
  //   uint8_t B=0x00;    
  // } RenderColors;

  // SDL_Color getColor();
  SDL_Color C_GREEN={ 0x00, 0x80,0x00};
  SDL_Color C_BLUE={ 0x00, 0x00,0xFF};
  SDL_Color C_RED={ 0xFF, 0x00,0x00};
  SDL_Color C_HEAD={0x00, 0x7A, 0xCC};
  SDL_Color C_BODY={0xFF, 0xFF, 0xFF};
   
  SDL_Color CellQ2Color(Cell::CellQ); 
 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Texture *texture, *text;
  TTF_Font* font;
  SDL_Rect block;
  

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif