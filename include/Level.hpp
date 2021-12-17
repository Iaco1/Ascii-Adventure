#pragma once
#include "Hero.hpp"
#include "LinkedList.hpp"
#include "MiscFunctions.hpp"

class Level{
    protected:
    LinkedList <Object> terrain;
    LinkedList <Entity> enemies;
    LinkedList <Entity> bonuses;
    LinkedList <Entity> maluses;
    LinkedList <Entity> bullets;
    int horBound;
    int vertBound;

    public:
    Level();
    Level(int w, int h); //creates a level randomly
    LinkedList<Object>* getTerrain();
    LinkedList<Entity>* getEnemies();
    LinkedList<Entity>* getBonuses();
    LinkedList<Entity>* getMaluses();
    LinkedList<Entity>* getBullets();
    template <class T>
    TileType elementAtIn(int x, int y, LinkedList<T> list);
    TileType elementAt(int x, int y);
    bool checkOverlap(int x1, int y1, int x2, int y2, TileType tile = TileType::EMPTY); //if tile = empty, checks for any kind of object
    void placePlatform(int height, int leftBound, int rightBound);
    int findClosestTerrain(int height, int xPosition, bool left);
    void generatePlatforms(int height, int averageXPosition, int leftBound, int rightBound, int currentIteration);
    //void spawnEnemies(int currentLevel);
};