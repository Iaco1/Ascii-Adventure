#include "Hero.hpp"

Hero::Hero(){}
Hero::Hero(int x, int y, int hp, int basicAttackDP, Weapon weapon) : Entity(x,y, TileType::HERO, hp, basicAttackDP, Direction::RIGHT){
    this->weapon = weapon;
    this->maxHp = 100;
}

Weapon* Hero::getWeapon(){ return &weapon; }

int Hero::getMaxHp(){ return maxHp; }
void Hero::setMaxHp(int maxHp){
    if(maxHp>0) this->maxHp = maxHp;
}

void Hero::setHp(int hp){
    if(hp<=maxHp) this->hp = hp;
    else this->hp = maxHp;
}

