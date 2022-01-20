#pragma once
#include "Item.hpp"

enum class MalusType{ THORN, SIZE };

class Malus : public Item{
    protected:
    MalusType mt;
    int quantity;

    public:
    Malus();
    Malus(int x, int y, TileType tileType, int hp, int dp, MalusType bt, int quantity);
    char getTileChar();

};