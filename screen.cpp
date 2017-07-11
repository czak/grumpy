#include <SDL.h>
#include <SDL_image.h>

#include "screen.h"
#include "cleanup.h"

bool Screen::initialize() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    return false;
  }

  win = SDL_CreateWindow("Floppy", 1270, 810, 640, 360, SDL_WINDOW_SHOWN);
  if (win == nullptr) {
    return false;
  }

  ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (ren == nullptr) {
    cleanup(win);
    return false;
  }

  bgTexture = IMG_LoadTexture(ren, "res/layer-1.png");
  if (bgTexture == nullptr) {
    cleanup(ren, win);
    return false;
  }

  floorTexture = IMG_LoadTexture(ren, "res/layer-2.png");
  if (floorTexture == nullptr) {
    cleanup(bgTexture, ren, win);
    return false;
  }

  birdTexture = IMG_LoadTexture(ren, "res/bat-1.png");
  if (birdTexture == nullptr) {
    cleanup(bgTexture, floorTexture, ren, win);
    return false;
  }

  brickTexture = IMG_LoadTexture(ren, "res/brick.png");
  if (brickTexture == nullptr) {
    cleanup(bgTexture, floorTexture, birdTexture, ren, win);
    return false;
  }

  return true;
}

void Screen::close() {
  cleanup(bgTexture, floorTexture, birdTexture, ren, win);
  SDL_Quit();
}

void Screen::clear() {
  SDL_RenderClear(ren);
}

void Screen::drawBackground(int position) {
  SDL_Rect rect { (position / 2) % 720, 0, 640, 360 };
  SDL_RenderCopy(ren, bgTexture, &rect, NULL);
  rect = { position % 720, 0, 640, 360 };
  SDL_RenderCopy(ren, floorTexture, &rect, NULL);
}

void Screen::drawBird(int x, int y, bool highlight = false) {
  const SDL_Rect birdRect { x, y, 64, 65 };
  if (highlight) {
    SDL_SetRenderDrawColor(ren, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(ren, &birdRect);
  }
  SDL_RenderCopy(ren, birdTexture, NULL, &birdRect);
}

void Screen::drawObstacle(int x, int numBricks, int position) {
  SDL_Rect rect { x - position, 360-48-32, 64, 32 };
  for (int i = 0; i < numBricks; i++) {
    SDL_RenderCopy(ren, brickTexture, NULL, &rect);
    rect.y -= 30;
  }
}

void Screen::present() {
  SDL_RenderPresent(ren);
}

const char* Screen::getError() {
  return SDL_GetError();
}
