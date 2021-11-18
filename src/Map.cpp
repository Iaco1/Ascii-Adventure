#include "Map.hpp"

Map::Map(){}
Map::Map(int w, int h){
    map.pushHead(new Node<Level>(Level(w,h)));
}