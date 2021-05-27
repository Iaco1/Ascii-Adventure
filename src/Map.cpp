#include <iostream>
#include "Map.hpp"

using namespace std;

Map::Map(int size) {
    for (int i = 0; i < size; i++) {
        Level newLvl;
        map.pushTail(newLvl);
    }
}

void Map::printMap() {
    for (int i = 0; i < map.getSize(); i++) {
        cout << endl << map[i].to_string() << endl;
    }
}