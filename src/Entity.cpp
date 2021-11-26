#include "Entity.hpp"

Entity::Entity() : Object(){}
Entity::Entity(int x, int y, TileType tiletype, Action action, int hp, int basicAttackDP) : Object(x,y,tiletype){
    this->action = action;
    this->hp = hp;
    
    if(basicAttackDP>0 || basicAttackDP==0) this->basicAttackDP = basicAttackDP;
    else this->basicAttackDP = 0;
}

void Entity::setAction(Action action){ this->action = action; }
Action Entity::getAction(){ return action; }

