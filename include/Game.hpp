#pragma once
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
    void addLevel();
    void draw(bool changeLevel);
    void drawHero();
    void drawHUD(WINDOW* hud);
    void drawBullets();
    void drawEnemies();
    void drawDoors();
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
    Action endOfFallingAction(Action proposedAction);
    
    void moveBullets();
    void nextXyFor(int &x, int &y, Animation animation);
    int getCorrespondingDelay(Animation animation);
    
    //buries (deletes) the dead entities (currently Enemies, Bonuses, Maluses and the Hero if he happens to die)
    //call using mortician(TileType::ENEMY)
    template <class T>
    void sweepItemsIn(LinkedList<T>* list){
	    Node<T>* iter = list->getHead();
	    while(iter!=NULL){
    	    if(iter->data.getHp()<=0) list->popNode(iter);
		    iter = iter->next;
	    }
    }
    void mortician(TileType tt = TileType::ENEMY); 

    void fallingAttack(int x, int y);
    void completeJump(Animation &proposedAnimation, Initiator &proposedInitiator);
    void fallingMechanic(Animation &proposedAnimation, Initiator &proposedInitiator);
    void grabBonusAt(int x, int y);
    void inflictMalusAt(int x, int y);
    void gainXpAt(int x, int y);

    void moveEnemies();
    Menu getMenu();
    void saveMapToFile();
    char getTTchar(TileType tt);
};