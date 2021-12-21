#include "Bonus.hpp"

Bonus::Bonus(){}

Bonus::Bonus(int x, int y, TileType tileType, int hp, int dp, BonusType bt, int quantity) : Item(x,y,tileType, hp, dp){
    if(dp>0) dp = 0;
    this->bt = bt;
    this->quantity = quantity;
}

char Bonus::getTileChar(){
    char bonusChar[]{ '+', 'A'};
    return bonusChar[(int)bt];
}