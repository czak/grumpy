class Screen;

class Game {
  public:
    void handleEvents();
    void update();
    void render(Screen& screen);
    bool isRunning();

  private:
    bool running = true;
    int position = 0;
    int x = 10;
    int y = 10;
};
