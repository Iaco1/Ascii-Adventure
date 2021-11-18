#include "Menu.hpp"
#include "Map.hpp"

class Game {
protected:
    bool gameOver;
    Menu menu;
    Map map;
    Window window;
    int score;

public:
    Game();
    void mainLoop();
    void updateMap();
    void draw();
    void input();
    void logic();
    Menu getMenu();
};