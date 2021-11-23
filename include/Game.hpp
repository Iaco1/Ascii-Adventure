#include "Menu.hpp"
#include "Level.hpp"

class Game {
protected:
    bool gameOver;
    Menu menu;
    LinkedList<Level> map;
    Hero hero;
    int currentLevel;
    Window window;
    int score;

public:
    Game();
    void mainLoop();
    void createMap();
    void updateMap();
    void draw();
    void input();
    void logic();
    Menu getMenu();
};