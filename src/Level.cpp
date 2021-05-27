#include <iostream>
#include "Level.hpp"

using namespace std;

Level::Level() {
    for (int i = 0; i < WINDOW_HEIGHT; i++) {
        for (int j = 0; j < WINDOW_WIDTH; j++)
            Board[i][j] = TileType::EMPTY;
    }
}

Level::Level(double fillPercentage) {
    //tba
}

char* Level::to_string() {
    char* levelOutput = new char[WINDOW_HEIGHT * (WINDOW_WIDTH + 1)];
    int count = 0;
    for (int i = 0; i < WINDOW_HEIGHT; i++, count++) {
        for (int j = 0; j < WINDOW_WIDTH; j++, count++)
            levelOutput[count] = TileChar[(int)Board[i][j]];
        levelOutput[count] = count == WINDOW_HEIGHT * (WINDOW_WIDTH + 1) - 1 ? '\0' : '\n';
    }
    return levelOutput;
}