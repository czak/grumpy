#include <SDL.h>

#include "game.h"
#include "screen.h"

void Game::handleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type != SDL_KEYDOWN) continue;
    running = false;
  }
}

void Game::render(Screen& screen) {
  screen.clear();
  screen.drawBackground();
  screen.drawBird(10, 10);
  screen.present();
}

bool Game::isRunning() {
  return running;
}
