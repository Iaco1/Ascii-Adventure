#include "Hero.hpp"

Hero::Hero(){}
Hero::Hero(int x, int y, TileType tiletype, Direction direction, int hp, int speed, int basicAttackDP) : Entity(x,y,tiletype, direction, hp, speed, basicAttackDP){}