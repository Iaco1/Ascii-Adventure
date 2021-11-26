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

    //one enemy standing at the opposite side of the map with respect to the hero
    enemies.pushHead(new Node<Entity>(Entity(w-1,h-1, TileType::ENEMY, Action::STILL, 100, 30 )));
     
}
LinkedList <Object> Level::getTerrain(){ return terrain; }
LinkedList <Entity> Level::getEnemies(){ return enemies; }
LinkedList <Entity> Level::getBonuses(){ return bonuses; }
LinkedList <Entity> Level::getMaluses(){ return maluses; }

template <class T>
TileType Level::elementAtIn(int x, int y, LinkedList<T> list){
    int x1, y1;
    for(int i=0; i<list.getSize(); i++){
        list[i].getXY(x1, y1);
        if(x == x1 && y == y1) return list[i].getTileType();
    }
    return TileType::EMPTY;
}

TileType Level::elementAt(int x, int y){
    if(elementAtIn(x,y, terrain) != TileType::EMPTY) return elementAtIn(x,y,terrain);
    else if(elementAtIn(x,y, enemies) != TileType::EMPTY) return elementAtIn(x,y,enemies);
    else if(elementAtIn(x,y, bonuses) != TileType::EMPTY) return elementAtIn(x,y,bonuses);
    else if(elementAtIn(x,y, maluses) != TileType::EMPTY) return elementAtIn(x,y,maluses);
    else return TileType::EMPTY;
}
