#include "Level.hpp"

Level::Level(){}
Level::Level(int w, int h){
    //insert randomly generating level code here
    //as of now, it contains the 'floor'

    //floor generation
    for(int i=0; i<=w; i++) terrain.pushHead(new Node<Object>(Object(i, h, TileType::TERRAIN)));

    //platform generation
    //creates one 3-character long platform
    for(int i=0; i<6; i++) terrain.pushHead(new Node<Object>(Object(1+i, h-3, TileType::TERRAIN))); 
}
LinkedList <Object> Level::getTerrain(){ return terrain; }
LinkedList <Entity> Level::getEnemies(){ return enemies; }
LinkedList <Entity> Level::getBonuses(){ return bonuses; }
LinkedList <Entity> Level::getMaluses(){ return maluses; }