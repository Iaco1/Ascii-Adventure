#pragma once
#include "Item.hpp"

enum class BonusType{ HP, AMMO, SIZE };

class Bonus : public Item{
    protected:
    BonusType bt;
    int quantity;
    
    public:
    Bonus();
    Bonus(int x, int y, TileType tileType, int hp, int dp, BonusType bt, int quantity);
    char getTileChar();
};