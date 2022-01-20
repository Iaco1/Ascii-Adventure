#include "Bonus.hpp"

Bonus::Bonus(){}

Bonus::Bonus(int x, int y, int hp, BonusType bt, int quantity) : Item(x,y,TileType::BONUS, hp, 0){
    this->bt = bt;
    this->quantity = quantity;
}

char Bonus::getTileChar(){
    char bonusChar[]{ '+', 'A'};
    return bonusChar[(int)bt];
}