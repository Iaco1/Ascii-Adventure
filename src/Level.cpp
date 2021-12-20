#include <iostream>
#include "Level.hpp"
#include "MiscFunctions.hpp"

Level::Level() {}
Level::Level(int w, int h) {
    horBound = w;
    vertBound = h;
    //insert randomly generating level code here
    //as of now, it contains the 'floor'

    //floor generation
    for (int i = 0; i <= w; i++) terrain.pushHead(new Node<Object>(Object(i, h, TileType::TERRAIN)));

    //platform generation
    //creates one 3-character long platform
    for (int i = 0; i < 6; i++) terrain.pushHead(new Node<Object>(Object(1 + i, h - 3, TileType::TERRAIN)));

    bonuses.pushHead(new Node<Entity>(Entity(2, h-4, TileType::BONUS, 100, 0, Direction::LEFT)));

    maluses.pushHead(new Node<Entity>(Entity(w/2, h-1, TileType::MALUS, 100, 20, Direction::RIGHT)));

    //one enemy standing at the opposite side of the map with respect to the hero
    enemies.pushHead(new Node<Entity>(Entity(w-1,h-1, TileType::ENEMY, 100, 30, Direction::LEFT)));

    
     
}
LinkedList <Object>* Level::getTerrain(){ return &terrain; }
LinkedList <Entity>* Level::getEnemies(){ return &enemies; }
LinkedList <Entity>* Level::getBonuses(){ return &bonuses; }
LinkedList <Entity>* Level::getMaluses(){ return &maluses; }
LinkedList <Entity>* Level::getBullets(){ return &bullets; }



int Level::countObjectsAt(int x, int y){
    return countObjectsAtIn(x,y, terrain)
        +countObjectsAtIn(x,y, enemies)
        +countObjectsAtIn(x,y, bonuses)
        +countObjectsAtIn(x,y, maluses)
        +countObjectsAtIn(x,y, bullets);
}

LinkedList<TileType> Level::getListOfTileTypesAt(int x, int y){
    LinkedList<TileType> list;
    for(int i=0; i<countObjectsAtIn(x,y,terrain); i++) list.pushHead(new Node<TileType>(TileType::TERRAIN));
    for(int i=0; i<countObjectsAtIn(x,y,enemies); i++) list.pushHead(new Node<TileType>(TileType::ENEMY));
    for(int i=0; i<countObjectsAtIn(x,y,bonuses); i++) list.pushHead(new Node<TileType>(TileType::BONUS));
    for(int i=0; i<countObjectsAtIn(x,y,maluses); i++) list.pushHead(new Node<TileType>(TileType::MALUS));
    for(int i=0; i<countObjectsAtIn(x,y,bullets); i++) list.pushHead(new Node<TileType>(TileType::BULLET));
    
    return list;
}

bool Level::checkOverlap(int x1, int y1, int x2, int y2, TileType tile /*= TileType::EMPTY*/) {
    if (tile == TileType::EMPTY || tile == TileType::TERRAIN) {
        Node<Object>* iter = terrain.getHead();
        while (iter != NULL) {
            if (iter->data.getX() >= x1 && iter->data.getX() <= x2 && iter->data.getY() >= y1 && iter->data.getY() <= y2)
                return true;
            iter = iter->next;
        }
    }
    if (tile == TileType::EMPTY || tile == TileType::ENEMY) {
        Node<Entity>* iter = enemies.getHead();
        while (iter != NULL) {
            if (iter->data.getX() >= x1 && iter->data.getX() <= x2 && iter->data.getY() >= y1 && iter->data.getY() <= y2)
                return true;
            iter = iter->next;
        }
    }
    if (tile == TileType::EMPTY || tile == TileType::BONUS) {
        Node<Entity>* iter = bonuses.getHead();
        while (iter != NULL) {
            if (iter->data.getX() >= x1 && iter->data.getX() <= x2 && iter->data.getY() >= y1 && iter->data.getY() <= y2)
                return true;
            iter = iter->next;
        }
    }
    if (tile == TileType::EMPTY || tile == TileType::MALUS) {
        Node<Entity>* iter = maluses.getHead();
        while (iter != NULL) {
            if (iter->data.getX() >= x1 && iter->data.getX() <= x2 && iter->data.getY() >= y1 && iter->data.getY() <= y2)
                return true;
            iter = iter->next;
        }
    }
    return false;
}

void Level::placePlatform(int height, int leftBound, int rightBound) {
    for (int i = leftBound; i <= rightBound; i++) {
        terrain.pushHead(new Node<Object>(Object(i, height, TileType::TERRAIN)));
    }
}

int Level::findClosestTerrain(int height, int xPosition, bool left) {
    int l = -1, r = horBound + 1;
    Node<Object>* iter = terrain.getHead();
    while (iter != NULL) {
        if (iter->data.getY() >= height - 1 && iter->data.getY() <= height + 1) {
            if (iter->data.getX() < xPosition && iter->data.getX() > l) l = iter->data.getX();
            if (iter->data.getX() > xPosition && iter->data.getX() < r) r = iter->data.getX();
        }
        iter = iter->next;
    }
    if (left) return l;
    else return r;
}

//work in progress
void Level::generatePlatforms(int height, int averageXPosition, int leftBound, int rightBound, int currentIteration) {
    int platformLength = diceDistribution(2, rightBound - leftBound + 1, 5, round(2 + currentIteration / 3));
    //reduce platform length in relation to available free space
    int platformOffset = randInt(max(0, leftBound - averageXPosition + platformLength - 1), min(platformLength - 1, rightBound - averageXPosition));
    int xPos1 = averageXPosition - platformLength + 1 + platformOffset;
    int xPos2 = averageXPosition + platformOffset;
    placePlatform(height, xPos1, xPos2);

    //tba: randomize order of new platform generation

    //new up-center platform
    if (randBool(0.5 /*probability in relation to iteration wip*/)) {
        int newXPos = xPos1 - 1 + platformLength / 2;
        if (!checkOverlap(newXPos - 2, height - 3, newXPos + 2, height - 1)) {
            generatePlatforms(height - 2, newXPos, findClosestTerrain(height - 2, newXPos, true), findClosestTerrain(height - 2, newXPos, false), currentIteration + 1);
        }
    }
    //new up-right platform
    if (randBool(0.5 /*probability in relation to iteration wip*/)) {
        if (!checkOverlap(xPos2 + 2, height - 3, xPos2 + 2, height - 1)) {
            generatePlatforms(height - 2, xPos2, findClosestTerrain(height - 2, xPos2, true), findClosestTerrain(height - 2, xPos2, false), currentIteration + 1);
        }
    }
    //new up-left platform
    if (randBool(0.5 /*probability in relation to iteration wip*/)) {
        if (!checkOverlap(xPos1 - 2, height - 3, xPos1 + 2, height - 1)) {
            generatePlatforms(height - 2, xPos1, findClosestTerrain(height - 2, xPos1, true), findClosestTerrain(height - 2, xPos1, false), currentIteration + 1);
        }
    }

    //new right platform
    if (randBool(0.5 /*probability in relation to iteration wip*/)) {
        if (!checkOverlap(xPos2 + 2, height - 1, xPos2 + 4, height + 1)) {
            generatePlatforms(height, xPos2 + 2, findClosestTerrain(height, xPos2 + 2, true), findClosestTerrain(height, xPos2 + 2, false), currentIteration + 1);
        }
    }

    //new left platform
    if (randBool(0.5 /*probability in relation to iteration wip*/)) {
        if (!checkOverlap(xPos1 - 2, height - 1, xPos1 - 4, height + 1)) {
            generatePlatforms(height - 2, xPos1 - 2, findClosestTerrain(height - 2, xPos1 - 2, true), findClosestTerrain(height - 2, xPos2 + 2, false), currentIteration + 1);
        }
    }

    //possibly new lower platforms
}