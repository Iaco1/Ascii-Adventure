#include "Item.hpp"

Item::Item(){

}

Item::Item(int x, int y, TileType tileType, int hp, int basicAttackDp) : Object(x,y,tileType){
    if(hp>=0) this->hp = hp;
    else this->hp = 100;

    if(basicAttackDp>=0) this->basicAttackDp = basicAttackDp;
    else this->basicAttackDp = 0;
}

int Item::getHp(){ return hp; }

void Item::setHp(int hp){
    this->hp = hp;
    // if(hp == 0) call destructor 
}

int Item::getBasicAttackDp(){ return basicAttackDp; }