#include "Menu.hpp"
#include "Level.hpp"

class Game {
protected:
    bool gameOver;
    Menu menu;
    LinkedList<Level> map;
    Hero hero;
    int currentLevel;
    WINDOW* levelWindow; //the window in which we display the currentLevel
    int score;

public:
    Game();
    void mainLoop();
    void createMap();
    void updateMap();
    void draw(bool newLevel);
    void drawHero();
    void drawHUD(WINDOW* hud);
    void drawBullets();
    template <class T>
    void drawLevelElements(LinkedList<T> list);
    Action input();
    void logic(Action proposedAction);
    Animation getCorrespondingAnimation(char userKey);
    Action getCorrespondingAction(Animation animation, Initiator initator);
    
    Menu getMenu();
};