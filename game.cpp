#include <SDL.h>

#include "game.h"
#include "screen.h"

Game::Game() {
  obstacles[0].x = 200;
  obstacles[0].numBricks = 3;
  obstacles[1].x = 400;
  obstacles[1].numBricks = 6;
  obstacles[2].x = 600;
  obstacles[2].numBricks = 4;
  obstacles[3].x = 800;
  obstacles[3].numBricks = 7;
  obstacles[4].x = 1000;
  obstacles[4].numBricks = 5;
}

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

void Game::update() {
  position++;
}

void Game::render(Screen& screen) {
  screen.clear();
  screen.drawBackground(position);
  screen.drawBird(x, y);
  for (auto o : obstacles) {
    screen.drawObstacle(o.x, o.numBricks, position);
  }
  screen.present();
}

bool Game::isRunning() {
  return running;
}
