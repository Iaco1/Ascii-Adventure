#include "LinkedList.hpp"
#include "Level.hpp"

class Map {
protected:
    LinkedList<Level> map;
    WINDOW* lvlWin;
    int windowHeight, windowWidth;
    int currentLvl;

public:
    Map();
    void mapLoop();
    void generateLvl();
    void nextLvl();
    void prevLvl();
    void refreshMap();
    char* to_string();
};