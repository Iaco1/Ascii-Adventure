#include "Entity.hpp"

Entity::Entity() : Object(){}
Entity::Entity(int x, int y, TileType tiletype, Direction direction, int hp, int speed, int basicAttackDP) : Object(x,y,tiletype){
    this->direction = direction;
    this->hp = hp;
    
    if(basicAttackDP>0 || basicAttackDP==0) this->basicAttackDP = basicAttackDP;
    else this->basicAttackDP = 0;

    if(speed>0 || speed == 0 ) this->speed = speed;
    else this->speed = 0;
}

void Entity::setDirection(Direction direction){ this->direction = direction; }
Direction Entity::getDirection(){ return direction; }
void Entity::setSpeed(int speed){ 
    if(speed > 0 && speed < 10) this->speed = speed;
    else this->speed = 1;
}
int Entity::getSpeed(){ return speed; }

