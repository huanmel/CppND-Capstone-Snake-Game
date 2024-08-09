#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height)
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  if (IMG_Init(IMG_INIT_PNG) < 0)
  {
    std::cerr << "Error initializing SDL_image: " << IMG_GetError() << std::endl;
  }

  // Initialize SDL_ttf
  if (TTF_Init() < 0)
  {
    std::cerr << "Error intializing SDL_ttf: " << TTF_GetError() << std::endl;
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window)
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer)
  {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  SDL_Surface *buffer = IMG_Load(IMG_PATH);
  if (!buffer)
  {
    std::cerr << "Error loading image test.png: " << SDL_GetError() << std::endl;
  }

  texture = SDL_CreateTextureFromSurface(sdl_renderer, buffer);
  SDL_FreeSurface(buffer);
  buffer = NULL;
  if (!texture)
  {
    std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
  }

  font = TTF_OpenFont(FONT_PATH, 52);
  if (!font)
  {
    std::cerr << "Error loading font: " << TTF_GetError() << std::endl;
  }

  // Start sending SDL_TextInput events
  // SDL_StartTextInput();
}

Renderer::~Renderer()
{
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const &snake, std::shared_ptr<Food> fd1)
{
  SDL_Color C;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food

  int vecSize = fd1->getFoodSize();
  if (vecSize > 0)
  {
    for (unsigned int i = 0; i < vecSize; i++)
    {
      block.x = static_cast<int>(fd1->getX(i) * block.w);
      block.y = static_cast<int>(fd1->getY(i) * block.h);
      Cell::CellQ Q = fd1->getQ(i);
      C = CellQ2Color(Q);

      SDL_SetRenderDrawColor(sdl_renderer, C.r, C.g, C.b, C.a);
      SDL_RenderFillRect(sdl_renderer, &block);
    }
  }

  // my code
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  vecSize = snake._body2.getBodySize();
  // Render snake's head
  block.x = static_cast<int>(snake._body2.getX()) * block.w;
  block.y = static_cast<int>(snake._body2.getY()) * block.h;
  if (snake.alive)
  {

    C = C_HEAD;
  }
  else
  {

    C = C_RED;
  }
  SDL_SetRenderDrawColor(sdl_renderer, C.r, C.g, C.b, C.a);
  SDL_RenderFillRect(sdl_renderer, &block);
  if (vecSize > 1)
  {
    C = C_BODY;
    SDL_SetRenderDrawColor(sdl_renderer, C.r, C.g, C.b, C.a);
    for (unsigned int i = 1; i < vecSize; i++)
    {
      block.x = static_cast<int>(snake._body2.getX(i) * block.w);
      block.y = static_cast<int>(snake._body2.getY(i) * block.h);
      SDL_RenderFillRect(sdl_renderer, &block);
    }
  }

  SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderText(std::string input)
{
  // Clear the window to white
  // SDL_SetRenderDrawColor( sdl_renderer, 255, 255, 255, 255 );
  // SDL_RenderClear( sdl_renderer );
  // Render texture
  SDL_Rect dest_text;
  SDL_Rect dest_cmdline;
  dest_cmdline.w = screen_width;
  dest_cmdline.h = screen_height;
  dest_cmdline.x = 0;
  dest_cmdline.y = 0;
  SDL_RenderCopy(sdl_renderer, texture, NULL, &dest_cmdline);

  SDL_Color foreground = {0, 0, 0};
  if (input.size())
  {
    SDL_Surface *text_surf = TTF_RenderText_Solid(font, input.c_str(), foreground);
    text = SDL_CreateTextureFromSurface(sdl_renderer, text_surf);

    dest_text.x = dest_cmdline.x + 20;                    //- (text_surf->w / 2.0f);//320
    dest_text.y = dest_cmdline.y + dest_cmdline.h * 0.06; // 240;
    dest_text.w = text_surf->w;
    dest_text.h = text_surf->h * 0.6;
    SDL_RenderCopy(sdl_renderer, text, NULL, &dest_text);

    SDL_DestroyTexture(text);
    SDL_FreeSurface(text_surf);
  }

  // Update window
  SDL_RenderPresent(sdl_renderer);
}
SDL_Color Renderer::CellQ2Color(Cell::CellQ Q)
{
  SDL_Color C = {0, 0, 0, 0xff};
  switch (Q)
  {
  case Cell::CellQ::fHi:
    C = C_BLUE;
    break;
  case Cell::CellQ::fMe:
    C = C_GREEN;
    break;
  case Cell::CellQ::fLo:
    C = C_RED;
    break;
  }
  C.a = 0xff;
  return C;
}
void Renderer::UpdateWindowTitle(int score, int fps)
{
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
