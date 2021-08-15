#include <iostream>
#include <ncurses.h>
#include "Map.hpp"

using namespace std;

Map::Map() {
    windowHeight = WINDOW_HEIGHT;
    windowWidth = WINDOW_WIDTH;
    generateLvl();
    currentLvl = 0;
}

void Map::mapLoop() {
    lvlWin = newwin(windowHeight, windowWidth, 0, 0);
    refresh();
    refreshMap();
    int c = getch();
    //work in progress
}

void Map::generateLvl() {
    Level newLvl;
    //altro codice per randomizzare il livello
    map.pushTail(newLvl);
}

void Map::nextLvl() {
    if (currentLvl >= map.getSize() - 1) generateLvl();
    currentLvl++;
    //altro codice per impostare posiz. cursore
}

void Map::prevLvl() {
    if (currentLvl > 0) {
        currentLvl--;
        //altro codice per impostare posiz. cursore
    }
}

void Map::refreshMap() {
    mvwprintw(lvlWin, 0, 0, "%s", to_string());
    wrefresh(lvlWin);
}

char* Map::to_string() {
    return map[currentLvl].to_string();
}