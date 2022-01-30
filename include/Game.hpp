#pragma once
#include "Menu.hpp"
#include "Level.hpp"

/*
    this is the game's main class where things are being drawn, the laws of physics being applied (kind of)
    and the Hero's triumphs and losses happen

    - the gameOver flag determines whether to stop the game loop and go back to the main title screen
    - the menu object is a container for methods related to drawing the menu and to remember the user's choice in the menu 
    - the map is a doubly-linked list containing all of the in-game objects that are visible on the map except for the hero
    - the hero is the character the player controls
    - currentlevel is the index indicating what level the player is in
    - levelWindow is an ncurses WINDOW object thay is slightly smaller than the full stdscr WINDOW to accomodate the HUD
      it's where the map is drawn
    - score is a counter for the number of user collected XP objects
*/

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
    void draw(bool changeLevel, int hm);
    void drawHero(int hm);
    void drawHUD(WINDOW* hud);
    void drawBullets();
    void drawDoors();
    template <class T>
    void drawLevelElements(LinkedList<T> list);
    void drawEnemies();
    void drawBonuses();
    void drawMaluses();

    LinkedList<Action> input(int hm);
    int logic(LinkedList<Action> proposedActions);

    Animation getCorrespondingAnimation(char userKey);
    Action getCorrespondingAction(Animation animation, Initiator initator, TileType ttAffected);
    LinkedList<Action> getEngagedAction(Action proposedAction);
    LinkedList<Action> getEngagedAction(Action proposedAction, Enemy *enemy);
    
    Action goLeftRight(Action proposedAction);
    Action goLeftRight(Action proposedAction, Enemy *enemy);
    Action jump(Action proposedAction);
    Action fall(Action proposedAction);
    Action fall(Action proposedAction, Enemy *enemy);
    Action shoot(Action proposedAction);
    LinkedList<Action> endOfFallingAction(Action proposedAction);
    
    void moveBullets();
    void nextXyFor(int &x, int &y, Animation animation);
    int getCorrespondingDelay(Animation animation, TileType agent);
    void delay(LinkedList<Action> *pa, Action al[], TileType, int hm);
    
    //buries (deletes) the dead entities (currently Enemies, Bonuses, Maluses and the Hero if he happens to die)
    //call using mortician(TileType::ENEMY)
    template <class T>
    void sweepItemsIn(LinkedList<T>* list){
	    Node<T>* iter = list->getHead();
	    while(iter!=NULL){
    	    if(iter->data.getHp()<=0) {
                if(iter->data.getTileType() == TileType::ENEMY){
                    int x = iter->data.getX(), y = iter->data.getY();
                    mvwaddch(levelWindow, y, x, ' ');
                    mvwaddch(levelWindow, y, x+1, ' ');
                    mvwaddch(levelWindow, y, x-1, ' ');
                } 
                list->popNode(iter);
            }
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
    LinkedList<Action> horizontalPattern(Enemy *enemy);
    Menu getMenu();
};