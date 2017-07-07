#include <SDL.h>

#include "game.h"
#include "screen.h"

void Game::handleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      running = false;
    }
  }

  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_ESCAPE]) {
    running = false;
  }

  if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_H]) {
    x--;
  } else if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_L]) {
    x++;
  }

  if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_K]) {
    y--;
  } else if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_J]) {
    y++;
  }
}

void Game::render(Screen& screen) {
  screen.clear();
  screen.drawBackground();
  screen.drawBird(x, y);
  screen.present();
}

bool Game::isRunning() {
  return running;
}
