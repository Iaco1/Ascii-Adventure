#include "Hero.hpp"

Hero::Hero(){}
Hero::Hero(int x, int y, int hp, int speed, int basicAttackDP) : Entity(x,y, TileType::HERO, Direction::STILL, hp, speed, basicAttackDP){}