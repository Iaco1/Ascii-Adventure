#pragma once
#include "Object.hpp"
/*
item is a class in between Object and Entity
that serves the purpose of being a base class for Entity, Bonus and Malus

an item has health points and damage points
*/

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