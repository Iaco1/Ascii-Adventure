#include "LinkedList.hpp"
#include "Level.hpp"

class Map {
protected:
    LinkedList<Level> map;

public:
    Map(int size);      //generates a map list of size levels
    void printMap();    //prints each level  
};