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
    void draw(bool newLevel);
    void drawHero();
    template <class T>
    void drawLevelElements(LinkedList<T> list);
    Action input();
    void logic(Action proposedAction);
    Menu getMenu();
};