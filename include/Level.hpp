#pragma once
#include "Hero.hpp"
#include "LinkedList.hpp"
#include "MiscFunctions.hpp"
#include "Bonus.hpp"
#include "Malus.hpp"
#include "Enemy.hpp"


/*
this class contains all of the objects being drawn to the screen (except the hero) for the current level
- terrain contains the '#' represented elements, these are the platforms
- enemies, bonuses, maluses, bullets, xps, prevLevelDoor, nextLevelDoor contain exactly whay you would expect
*/
class Level {
protected:
    LinkedList <Object> terrain;
    LinkedList <Enemy> enemies;
    LinkedList <Bonus> bonuses;
    LinkedList <Malus> maluses;
    LinkedList <Entity> bullets;
    Object prevLevelDoor;
    Object nextLevelDoor;
    LinkedList <Object> xps; //experience points
    int horBound;
    int vertBound;

public:
    Level();
    Level(int w, int h, int levelIndex); //creates a level randomly
    LinkedList<Object>* getTerrain();
    LinkedList<Enemy>* getEnemies();
    LinkedList<Bonus>* getBonuses();
    LinkedList<Malus>* getMaluses();
    LinkedList<Entity>* getBullets();
    LinkedList<Object>* getXps();

    /*why this is here
    The implementation of a non-specialized template must be visible to a translation unit that uses it.

    The compiler must be able to see the implementation in order to generate code for all specializations in your code.

    This can be achieved in two ways:

    1) Move the implementation inside the header.

    2) If you want to keep it separate, move it into a different header which you include in your original header:
    */
   //returns the no. of objects of type T at coordinates (x,y) 
    template <class T>
    int countObjectsAtIn(int x, int y, LinkedList<T> list) {
        int i = 0;
        int x1, y1;
        Node<T>* iter = list.getHead();

        while (iter != NULL) {
            iter->data.getXY(x1, y1);
            if (x1 == x && y1 == y) i++;
            iter = iter->next;
        }
        return i;
    }

    //returns the Node of Type T at coordinates (x,y)
    template <class T>
    Node<T>* getNodeAtIn(int x, int y, LinkedList<T>* list) {
        Node<T>* iter = list->getHead();
        while (iter != NULL) {
            if (iter->data.getX() == x && iter->data.getY() == y) return iter;
            iter = iter->next;
        }
        return iter;
    }

    int countObjectsAt(int x, int y);
    LinkedList<TileType> getListOfTileTypesAt(int x, int y);
    Object getPrevLevelDoor();
    Object getNextLevelDoor();

    int getHorBound();
    int getVertBound();


    bool checkOverlap(int x1, int y1, int x2, int y2, TileType tile = TileType::EMPTY);
    void placePlatform(int height, int leftBound, int rightBound);
    int findClosestTerrain(int height, int xPosition, bool left);
    void generatePlatforms(int height, int averageXPosition, int leftBound, int rightBound, int currentIteration);
    void generateNLDoor();
    void findFreeSpace(int& x, int& y, int offset = 0);
    void spawnEnemies(int currentLevel);
    void spawnBonuses(int currentLevel);
    void spawnMaluses(int currentLevel);
    void spawnXp();
};