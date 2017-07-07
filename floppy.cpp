#include <iostream>
#include <SDL.h>

#include "screen.h"
#include "cleanup.h"

int main(int, char**) {
  Screen screen;

  if (!screen.initialize()) {
    std::cout << "Error: " << screen.getError() << "\n";
    screen.close();
    return 1;
  }

  SDL_Event event;
  bool active = true;

  while (active) {
    while (SDL_PollEvent(&event)) {
      if (event.type != SDL_KEYDOWN) continue;
      active = false;
    }

    screen.clear();
    screen.drawBackground();
    screen.present();

    SDL_Delay(16);
  }

  screen.close();
  return 0;
}
