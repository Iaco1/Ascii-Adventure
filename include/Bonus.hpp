#pragma once
#include "Hero.hpp"

enum class BonusType{ HP, AMMO, MAXAMMO, INSTAKILL, SIZE };

class Bonus : public Item{
    protected:
    BonusType bt;
    int quantity;
    
    public:
    Bonus();
    Bonus(int x, int y, int hp, BonusType bt, int quantity);
    void giveBonus(Hero *hero);
    char getTileChar();
};