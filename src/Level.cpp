#include <iostream>
#include <cmath>
#include "Level.hpp"
#include "MiscFunctions.hpp"

Level::Level() {}
Level::Level(int w, int h, int levelIndex) {
    horBound = w;
    vertBound = h;

    if (levelIndex > 0) prevLevelDoor = Object(1, h - 1, TileType::PL_DOOR);
    else prevLevelDoor = Object(); //this has TileType and thus should not be drawn
    nextLevelDoor = Object(w, h - 1, TileType::NL_DOOR);

    //floor generation
    for (int i = 0; i <= w; i++) terrain.pushHead(new Node<Object>(Object(i, h, TileType::TERRAIN)));

    //platform generation
    //creates one 3-character long platform
    for (int i = 0; i < 6; i++) terrain.pushHead(new Node<Object>(Object(1 + i, h - 3, TileType::TERRAIN)));

    bonuses.pushHead(new Node<Bonus>(Bonus(2, h-4, TileType::BONUS, 100, 0, BonusType::HP, 1)));
    maluses.pushHead(new Node<Malus>(Malus(w/2, h-1, TileType::MALUS, 100, 20, MalusType::THORN, 1)));
    enemies.pushHead(new Node<Entity>(Entity(w - 1, h - 1, TileType::ENEMY, 100, 30, Direction::LEFT)));
    xps.pushHead(new Node<Object>(Object(5, h-4, TileType::XP)));

    generatePlatforms(vertBound - 4, horBound / 2, 0, horBound - 1, 1);
}
LinkedList <Object>* Level::getTerrain(){ return &terrain; }
LinkedList <Entity>* Level::getEnemies(){ return &enemies; }
LinkedList <Bonus>* Level::getBonuses(){ return &bonuses; }
LinkedList <Malus>* Level::getMaluses(){ return &maluses; }
LinkedList <Entity>* Level::getBullets(){ return &bullets; }
LinkedList <Object>* Level::getXps(){ return &xps; }

int Level::countObjectsAt(int x, int y){
    return countObjectsAtIn(x,y, terrain)
        +countObjectsAtIn(x,y, enemies)
        +countObjectsAtIn(x,y, bonuses)
        +countObjectsAtIn(x,y, maluses)
        +countObjectsAtIn(x,y, bullets)
        +countObjectsAtIn(x,y, xps)
        + (prevLevelDoor.getX() == x && prevLevelDoor.getY() == y)
        + (nextLevelDoor.getX() == x && prevLevelDoor.getY() == y);
}

LinkedList<TileType> Level::getListOfTileTypesAt(int x, int y) {
    LinkedList<TileType> list;
    for(int i=0; i<countObjectsAtIn(x,y,terrain); i++) list.pushHead(new Node<TileType>(TileType::TERRAIN));
    for(int i=0; i<countObjectsAtIn(x,y,enemies); i++) list.pushHead(new Node<TileType>(TileType::ENEMY));
    for(int i=0; i<countObjectsAtIn(x,y,bonuses); i++) list.pushHead(new Node<TileType>(TileType::BONUS));
    for(int i=0; i<countObjectsAtIn(x,y,maluses); i++) list.pushHead(new Node<TileType>(TileType::MALUS));
    for(int i=0; i<countObjectsAtIn(x,y,bullets); i++) list.pushHead(new Node<TileType>(TileType::BULLET));
    for(int i=0; i<countObjectsAtIn(x,y,xps); i++) list.pushHead(new Node<TileType>(TileType::XP));

    if(prevLevelDoor.getX() == x && prevLevelDoor.getY() == y) list.pushHead(new Node<TileType>(TileType::PL_DOOR));
    if(nextLevelDoor.getX() == x && nextLevelDoor.getY() == y) list.pushHead(new Node<TileType>(TileType::NL_DOOR));
    
    return list;
}

Object Level::getPrevLevelDoor() { return prevLevelDoor; }
Object Level::getNextLevelDoor() { return nextLevelDoor; }
int Level::getHorBound(){ return horBound; }
int Level::getVertBound(){ return vertBound; }

bool Level::checkOverlap(int x1, int y1, int x2, int y2, TileType tile /*= TileType::EMPTY*/) {
    if (x1 < 0 || y1 < 0 || x2 > horBound || y2 > vertBound || x1 > x2 || y1 > y2) return true;
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
        Node<Bonus>* iter = bonuses.getHead();
        while (iter != NULL) {
            if (iter->data.getX() >= x1 && iter->data.getX() <= x2 && iter->data.getY() >= y1 && iter->data.getY() <= y2)
                return true;
            iter = iter->next;
        }
    }
    if (tile == TileType::EMPTY || tile == TileType::MALUS) {
        Node<Malus>* iter = maluses.getHead();
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
        if (iter->data.getY() >= height - 2 && iter->data.getY() <= height + 2) {
            if (iter->data.getX() < xPosition && iter->data.getX() > l) l = iter->data.getX();
            if (iter->data.getX() > xPosition && iter->data.getX() < r) r = iter->data.getX();
        }
        iter = iter->next;
    }
    if (left) return l;
    else return r;
}

void Level::generatePlatforms(int height, int averageXPosition, int leftBound, int rightBound, int currentIteration) {
    if (leftBound > rightBound || leftBound < 0 || rightBound > horBound || height < 0 || height > vertBound) return;
    int platformLength = Misc::diceDistribution(2, min((horBound + 1) / 4, rightBound - leftBound + 1), 5, round(2 + currentIteration / 3));
    int minOffset = max(0, averageXPosition - leftBound - platformLength + 1);
    int maxOffset = min(averageXPosition - leftBound, rightBound - leftBound - platformLength + 1);
    int platformOffset = Misc::randInt(minOffset, maxOffset);
    int xPos1 = leftBound + platformOffset;
    int xPos2 = xPos1 + platformLength - 1;
    placePlatform(height, xPos1, xPos2);

    double generateChance = 0.7 - 0.05 * currentIteration;

    int order[6] = { 1, 2, 3, 4, 5, 6 };
    Misc::shuffle(order, 6);

    for (int i = 0; i < 6; i++) {

        switch (i) {
        case 1:
            //new up-left platform
            if (Misc::randBool(generateChance)) {
                int hDiff = Misc::randInt(3, 4);
                if (!checkOverlap(xPos1 - 2, height - hDiff - 2, xPos1 + 2, height - hDiff + 2) && height - hDiff >= 3) {
                    generatePlatforms(height - hDiff, xPos1, findClosestTerrain(height - hDiff, xPos1, true) + 2, min(findClosestTerrain(height - hDiff, xPos1, false) - 2, xPos2 - 1), currentIteration + 1);
                }
            }
            break;

        case 2:
            //new up-right platform
            if (Misc::randBool(generateChance)) {
                int hDiff = Misc::randInt(3, 4);
                if (!checkOverlap(xPos2 - 2, height - hDiff - 2, xPos2 + 2, height - hDiff + 2) && height - hDiff >= 3) {
                    generatePlatforms(height - hDiff, xPos2, max(findClosestTerrain(height - hDiff, xPos2, true) + 2, xPos1 + 1), findClosestTerrain(height - hDiff, xPos2, false) - 2, currentIteration + 1);
                }
            }
            break;

        case 3:
            //new left platform
            if (Misc::randBool(generateChance)) {
                int hDiff = Misc::randInt(-1, 1);
                int dist = Misc::randInt(2, 3);
                if (!checkOverlap(xPos1 - dist - 4, height + hDiff - 2, xPos1 - dist, height + hDiff + 2) && height + hDiff >= 3) {
                    generatePlatforms(height + hDiff, xPos1 - dist, findClosestTerrain(height + hDiff, xPos1 - dist, true) + 2, xPos1 - dist, currentIteration + 1);
                }
            }
            break;

        case 4:
            //new right platform
            if (Misc::randBool(generateChance)) {
                int hDiff = Misc::randInt(-1, 1);
                int dist = Misc::randInt(2, 3);
                if (!checkOverlap(xPos2 + dist, height + hDiff - 2, xPos2 + dist + 4, height + hDiff + 2) && height + hDiff >= 3) {
                    generatePlatforms(height + hDiff, xPos2 + dist, xPos2 + dist, findClosestTerrain(height + hDiff, xPos2 + dist, false) - 2, currentIteration + 1);
                }
            }
            break;

        case 5:
            //new down-left platform
            if (Misc::randBool(generateChance)) {
                int hDiff = Misc::randInt(3, 4);
                if (!checkOverlap(xPos1 - 2, height + hDiff - 2, xPos1 + 2, height + hDiff + 2)) {
                    generatePlatforms(height + hDiff, xPos1, findClosestTerrain(height + hDiff, xPos1, true) + 2, findClosestTerrain(height + hDiff, xPos1, false) - 2, currentIteration + 1);
                }
            }
            break;

        case 6:
            //new down-right platform
            if (Misc::randBool(generateChance)) {
                int hDiff = Misc::randInt(3, 4);
                if (!checkOverlap(xPos2 - 2, height + hDiff - 2, xPos2 + 2, height + hDiff + 2)) {
                    generatePlatforms(height + hDiff, xPos2, findClosestTerrain(height + hDiff, xPos2, true) + 2, findClosestTerrain(height + hDiff, xPos2 + 2, false) - 2, currentIteration + 1);
                }
            }
            break;
        }

    }
}

/*
void Level::spawnEnemies(int currentLevel) {

}
*/