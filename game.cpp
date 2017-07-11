#include <SDL.h>
#include <list>
#include <cstdlib>

#include "game.h"
#include "screen.h"

Game::Game() {
  obstacles.push_back({ 200, std::rand() % 10 });
  obstacles.push_back({ 400, std::rand() % 10 });
  obstacles.push_back({ 600, std::rand() % 10 });
  obstacles.push_back({ 800, std::rand() % 10 });
  obstacles.push_back({ 1000, std::rand() % 10 });
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

  // Do we need a new obstacle?
  auto first = obstacles.front(); 
  auto last = obstacles.back(); 
  if (first.x - position + 64 < 0) {
    obstacles.pop_front();
    obstacles.push_back({ last.x + 200, std::rand() % 9 });
  }

  // Check for collisions
  collision = false;
  first = obstacles.front();
  if (x < (first.x + 64 - position) && x + 64 > first.x - position) {
    collision = true;
  }
}

void Game::render(Screen& screen) {
  screen.clear();
  screen.drawBackground(position);
  screen.drawBird(x, y, collision);
  for (auto o : obstacles) {
    screen.drawObstacle(o.x, o.numBricks, position);
  }
  screen.present();
}

bool Game::isRunning() {
  return running;
}
