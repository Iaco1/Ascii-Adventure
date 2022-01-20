#pragma once
#include "Item.hpp"

enum class MalusType{ THORN, SIZE };

class Malus : public Item{
    protected:
    MalusType mt;
    int quantity;

    public:
    Malus();
    Malus(int x, int y, int hp, int dp, MalusType mt, int quantity);
    char getTileChar();

};