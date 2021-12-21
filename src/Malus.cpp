#include "Malus.hpp"

Malus::Malus(){}

Malus::Malus(int x, int y, TileType tileType, int hp, int dp, MalusType mt, int quantity) : Item(x,y,tileType, hp, dp){
    if(dp>0) dp = 0;
    this->mt = mt;
    this->quantity = quantity;
}

char Malus::getTileChar(){
    char malusChar[]{ 'X'};
    return malusChar[(int)mt];
}