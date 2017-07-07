#include <iostream>

#include "screen.h"
#include "game.h"

int main(int, char**) {
  Screen screen;

  if (!screen.initialize()) {
    std::cout << "Error: " << screen.getError() << "\n";
    screen.close();
    return 1;
  }

  Game game;

  while (game.isRunning()) {
    game.handleEvents();
    game.update();
    game.render(screen);
  }

  screen.close();
  return 0;
}
