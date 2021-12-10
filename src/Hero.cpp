#include "Hero.hpp"

Hero::Hero(){}
Hero::Hero(int x, int y, int hp, int basicAttackDP, Weapon weapon) : Entity(x,y, TileType::HERO, hp, basicAttackDP, Direction::RIGHT){
    this->weapon = weapon;
}

Weapon Hero::getWeapon(){ return weapon; }