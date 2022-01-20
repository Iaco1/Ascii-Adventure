#include "Malus.hpp"

Malus::Malus(){}

Malus::Malus(int x, int y, int hp, int dp, MalusType mt, int quantity) : Item(x,y, TileType::MALUS, hp, dp){
    this->mt = mt;
    this->quantity = quantity;
}

char Malus::getTileChar(){
    char malusChar[]{ 'X'};
    return malusChar[(int)mt];
}