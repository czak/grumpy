class Screen;

class Game {
  public:
    void handleEvents();
    void render(Screen& screen);
    bool isRunning();

  private:
    bool running = true;
};
