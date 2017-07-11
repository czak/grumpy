class Screen;

struct Obstacle {
  int x;
  int numBricks;
};

class Game {
  public:
    Game();
    void handleEvents();
    void update();
    void render(Screen& screen);
    bool isRunning();

  private:
    bool running = true;
    int position = 0;
    int x = 10;
    int y = 10;
    Obstacle obstacles[5];
};
