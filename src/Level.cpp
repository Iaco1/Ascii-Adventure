#include <iostream>
#include <cmath>
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

    //one enemy standing at the opposite side of the map with respect to the hero
    enemies.pushHead(new Node<Entity>(Entity(w - 1, h - 1, TileType::ENEMY, 100, 30, Direction::LEFT)));

    generatePlatforms(vertBound - 4, horBound / 2, 0, horBound, 1);
}
LinkedList <Object>* Level::getTerrain() { return &terrain; }
LinkedList <Entity>* Level::getEnemies() { return &enemies; }
LinkedList <Entity>* Level::getBonuses() { return &bonuses; }
LinkedList <Entity>* Level::getMaluses() { return &maluses; }
LinkedList <Entity>* Level::getBullets() { return &bullets; }
template <class T>
TileType Level::elementAtIn(int x, int y, LinkedList<T> list) {
    int x1, y1;
    for (int i = 0; i < list.getSize(); i++) {
        list[i].getXY(x1, y1);
        if (x == x1 && y == y1) return list[i].getTileType();
    }
    return TileType::EMPTY;
}

TileType Level::elementAt(int x, int y) {
    if (elementAtIn(x, y, terrain) != TileType::EMPTY) return elementAtIn(x, y, terrain);
    else if (elementAtIn(x, y, enemies) != TileType::EMPTY) return elementAtIn(x, y, enemies);
    else if (elementAtIn(x, y, bonuses) != TileType::EMPTY) return elementAtIn(x, y, bonuses);
    else if (elementAtIn(x, y, maluses) != TileType::EMPTY) return elementAtIn(x, y, maluses);
    else return TileType::EMPTY;
}

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

void Level::generatePlatforms(int height, int averageXPosition, int leftBound, int rightBound, int currentIteration) {
    if (leftBound > rightBound || leftBound < 0 || rightBound > horBound || height < 0 || height > vertBound) return;
    int platformLength = Misc::diceDistribution(2, min(20, rightBound - leftBound + 1), 5, round(2 + currentIteration / 3));
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
                int hDiff = Misc::randInt(2, 4);
                if (!checkOverlap(xPos1 - 2, height - hDiff - 1, xPos1 + 2, height - hDiff + 1) && height - hDiff > 0) {
                    generatePlatforms(height - hDiff, xPos1, findClosestTerrain(height - hDiff, xPos1, true) + 2, min(findClosestTerrain(height - hDiff, xPos1, false) - 2, xPos2 - 1), currentIteration + 1);
                }
            }
            break;

        case 2:
            //new up-right platform
            if (Misc::randBool(generateChance)) {
                int hDiff = Misc::randInt(2, 4);
                if (!checkOverlap(xPos2 - 2, height - hDiff - 1, xPos2 + 2, height - hDiff + 1) && height - hDiff > 0) {
                    generatePlatforms(height - hDiff, xPos2, max(findClosestTerrain(height - hDiff, xPos2, true) + 2, xPos1 + 1), findClosestTerrain(height - hDiff, xPos2, false) - 2, currentIteration + 1);
                }
            }
            break;

        case 3:
            //new left platform
            if (Misc::randBool(generateChance)) {
                int hDiff = Misc::randInt(-1, 1);
                int dist = Misc::randInt(2, 3);
                if (!checkOverlap(xPos1 - dist - 4, height + hDiff - 1, xPos1 - dist, height + hDiff + 1) && height + hDiff > 0) {
                    generatePlatforms(height + hDiff, xPos1 - dist, findClosestTerrain(height + hDiff, xPos1 - dist, true) + 2, xPos1 - dist, currentIteration + 1);
                }
            }
            break;

        case 4:
            //new right platform
            if (Misc::randBool(generateChance)) {
                int hDiff = Misc::randInt(-1, 1);
                int dist = Misc::randInt(2, 3);
                if (!checkOverlap(xPos2 + dist, height + hDiff - 1, xPos2 + dist + 4, height + hDiff + 1) && height + hDiff > 0) {
                    generatePlatforms(height + hDiff, xPos2 + dist, xPos2 + dist, findClosestTerrain(height + hDiff, xPos2 + dist, false) - 2, currentIteration + 1);
                }
            }
            break;

        case 5:
            //new down-left platform
            if (Misc::randBool(generateChance)) {
                int hDiff = Misc::randInt(2, 4);
                if (!checkOverlap(xPos1 - 2, height + hDiff - 1, xPos1 + 2, height + hDiff + 1)) {
                    generatePlatforms(height + hDiff, xPos1, findClosestTerrain(height + hDiff, xPos1, true) + 2, findClosestTerrain(height + hDiff, xPos1, false) - 2, currentIteration + 1);
                }
            }
            break;

        case 6:
            //new down-right platform
            if (Misc::randBool(generateChance)) {
                int hDiff = Misc::randInt(2, 4);
                if (!checkOverlap(xPos2 - 2, height + hDiff - 1, xPos2 + 2, height + hDiff + 1)) {
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