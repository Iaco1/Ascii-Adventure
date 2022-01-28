#pragma once
#include "Entity.hpp"
#include "Weapon.hpp"


/*
    this class describes the character that the user can control
    the hero has a weapon and a maxHp which change during the game
*/
class Hero : public Entity{
    protected:
    Weapon weapon;
    int maxHp;

    public:
    Hero();
    Hero(int x, int y, int hp, int basicAttackDP, Weapon weapon);
    Weapon* getWeapon();
    int getMaxHp();
    void setMaxHp(int maxHp);
    void setHp(int hp);
};