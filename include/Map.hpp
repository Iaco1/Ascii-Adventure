#include "Level.hpp"

class Map{
    protected:
    LinkedList<Level> map;
    int currentLevel;
    public:
    Map();
    Map(int w, int h);
};