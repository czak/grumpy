#include <iostream>
#include <SDL.h>

#include "cleanup.h"

int main(int, char**) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL_Init Error: " << SDL_GetError() << "\n";
    return 1;
  }

  SDL_Window *win = SDL_CreateWindow("Floppy", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
  if (win == nullptr) {
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (ren == nullptr) {
    cleanup(win);
    std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << "\n";
    SDL_Quit();
    return 1;
  }

  std::string imagePath = "hello.bmp";
  SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
  if (bmp == nullptr) {
    cleanup(ren, win);
    std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << "\n";
    SDL_Quit();
    return 1;
  }

  SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
  cleanup(bmp);
  if (tex == nullptr) {
    cleanup(ren, win);
    std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << "\n";
    SDL_Quit();
    return 1;
  }

  for (int i = 0; i < 1; ++i) {
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);
    SDL_Delay(1000);
  }

  cleanup(tex, ren, win);
  SDL_Quit();
  return 0;
}
