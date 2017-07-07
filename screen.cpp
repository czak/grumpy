#include <SDL.h>
#include <SDL_image.h>

#include "screen.h"
#include "cleanup.h"


bool Screen::initialize() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    return false;
  }

  win = SDL_CreateWindow("Floppy", 1270, 690, 640, 360, SDL_WINDOW_SHOWN);
  if (win == nullptr) {
    return false;
  }

  ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (ren == nullptr) {
    cleanup(win);
    return false;
  }

  bgTexture = IMG_LoadTexture(ren, "res/full-background.png");
  if (bgTexture == nullptr) {
    cleanup(ren, win);
    return false;
  }

  return true;
}

void Screen::close() {
  cleanup(bgTexture, ren, win);
  SDL_Quit();
}

void Screen::clear() {
  SDL_RenderClear(ren);
}

void Screen::drawBackground() {
  SDL_RenderCopy(ren, bgTexture, NULL, NULL);
}

void Screen::present() {
  SDL_RenderPresent(ren);
}

const char* Screen::getError() {
  return SDL_GetError();
}
