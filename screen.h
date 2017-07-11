#include <SDL.h>

class Screen {
  public:
    bool initialize();
    void close();

    void clear();
    void drawBackground(int);
    void drawBird(int x, int y, bool highlight);
    void drawObstacle(int x, int numBricks, int position);
    void present();

    const char* getError();

  private:
    SDL_Window* win;
    SDL_Renderer* ren;

    // Textures
    SDL_Texture *bgTexture;
    SDL_Texture *floorTexture;
    SDL_Texture *birdTexture;
    SDL_Texture *brickTexture;
};
