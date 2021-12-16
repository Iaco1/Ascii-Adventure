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
    void drawEnemies();
    template <class T>
    void drawLevelElements(LinkedList<T> list);
    LinkedList<Action> input();
    void logic(LinkedList<Action> proposedActions);
    Animation getCorrespondingAnimation(char userKey);
    Action getCorrespondingAction(Animation animation, Initiator initator, TileType ttAffected);
    Action getEngagedAction(Action proposedAction);
    Action goLeftRight(Action proposedAction);
    Action jump(Action proposedAction);
    Action fall(Action proposedAction);
    Action shoot(Action proposedAction);
    void moveBullets();
    void nextXyFor(int &x, int &y, Animation animation);
    int getCorrespondingDelay(Animation animation);
    void mortician();
    Action fallingAttack(Action proposedAction);
    void completeJump(Animation &proposedAnimation, Initiator &proposedInitiator);
    void fallingMechanic(Animation &proposedAnimation, Initiator &proposedInitiator);
    Menu getMenu();
};