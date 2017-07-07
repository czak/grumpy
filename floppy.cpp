#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "cleanup.h"

struct Bird {
  SDL_Rect rect {0, 0, 64, 56};
  SDL_Texture* textures[4];
};

int main(int, char**) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL_Init Error: " << SDL_GetError() << "\n";
    return 1;
  }

  SDL_Window *win = SDL_CreateWindow("Floppy", 1270, 690, 640, 360, SDL_WINDOW_SHOWN);
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

  SDL_Texture *bg = IMG_LoadTexture(ren, "res/full-background.png");
  if (bg == nullptr) {
    cleanup(ren, win);
    std::cout << "IMG_LoadTexture Error: " << SDL_GetError() << "\n";
    SDL_Quit();
    return 1;
  }

  Bird bird;

  std::string basePath = "res/frame-";
  for (auto i : {0, 1, 2, 3}) {
    auto path = basePath + std::to_string(i) + ".png";
    bird.textures[i] = IMG_LoadTexture(ren, path.c_str());
    if (bird.textures[i] == nullptr) {
      cleanup(bg, ren, win);
      std::cout << "IMG_LoadTexture Error: " << SDL_GetError() << "\n";
      SDL_Quit();
      return 1;
    }
  }

  int frame = 0;
  bool isActive = true;
  while (isActive) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        isActive = false;
      }
    }

    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, bg, NULL, NULL);
    SDL_RenderCopy(ren, bird.textures[(++frame/3)%4], NULL, &bird.rect);
    SDL_RenderPresent(ren);

    SDL_Delay(16);
  }

  cleanup(bg, bird.textures[0], bird.textures[1], bird.textures[2], bird.textures[3], ren, win);
  SDL_Quit();
  return 0;
}
