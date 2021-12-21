#pragma once
#include "Object.hpp"

class Item : public Object{
    protected:
    int hp; //health points
    int dp; //Damage points

    public:
    Item();
    Item(int x, int y, TileType tileType, int hp, int dp);
    int getHp();
    void setHp(int hp);
    int getDp();
};