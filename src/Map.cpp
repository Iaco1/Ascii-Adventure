#include "Map.hpp"

Map::Map(){}
Map::Map(int w, int h){
    map.pushHead(Level(w,h));
}