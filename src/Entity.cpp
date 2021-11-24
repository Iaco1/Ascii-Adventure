#include "Entity.hpp"

Entity::Entity() : Object(){}
Entity::Entity(int x, int y, TileType tiletype, Direction direction, int hp, int basicAttackDP) : Object(x,y,tiletype){
    this->direction = direction;
    this->hp = hp;
    
    if(basicAttackDP>0 || basicAttackDP==0) this->basicAttackDP = basicAttackDP;
    else this->basicAttackDP = 0;
}

void Entity::setDirection(Direction direction){ this->direction = direction; }
Direction Entity::getDirection(){ return direction; }

