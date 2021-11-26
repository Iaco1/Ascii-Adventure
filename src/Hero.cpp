#include "Hero.hpp"

Hero::Hero(){}
Hero::Hero(int x, int y, int hp, int basicAttackDP) : Entity(x,y, TileType::HERO, Action::STILL, hp, basicAttackDP){}