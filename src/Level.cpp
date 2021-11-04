#include "Level.hpp"

Level::Level(){}
Level::Level(int w, int h){
    terrain.pushHead(Object(w/2, h/2, TileType::TERRAIN));
}