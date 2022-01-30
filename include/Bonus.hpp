#pragma once
#include "Hero.hpp"

enum class BonusType{ HP, AMMO, MAXAMMO, INSTAKILL, SIZE };

/*
The Bonus class describes attributes unique to bonuses such as:
- its BonusType bt, each BonusType awards the hero a different bonus such as
    HP: a health increse
    AMMO: an ammo increase
    MAXAMMO: a maxAmmo increase
    INSTAKILL: an increase in the weapon's damage points by a factor of 9000, which can kill almost any enemy in one shot
- its quantity: how much to increase the above-mentioned attributes
*/

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