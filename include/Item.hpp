#pragma once
#include "Object.hpp"

class Item : public Object{
    protected:
    int hp; //health points
    int basicAttackDp; //Damage points

    public:
    Item();
    Item(int x, int y, TileType tileType, int hp, int basicAttackDp);
    int getHp();
    void setHp(int hp);
    int getBasicAttackDp();
};