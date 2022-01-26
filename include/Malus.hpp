#pragma once
#include "Hero.hpp"

enum class MalusType{ THORN, LANDMINE, BARBED_WIRE, SIZE };

class Malus : public Item{
    protected:
    MalusType mt;
    int quantity;

    public:
    Malus();
    Malus(int x, int y, int hp, int dp, MalusType mt, int quantity);
    char getTileChar();
    void inflictMalusTo(Hero *hero);
};