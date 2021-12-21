#include "Action.hpp"

Action::Action(){
    animation = Animation::STILL;
    x=0; y=0;
    initiator = Initiator::LOGIC;
}

Action::Action(Animation animation, int x, int y, Initiator initiator, TileType ttAffected){
    this->animation = animation;
    
    if(x>=-1 && y>=0){
        this->x = x;
        this->y = y;
    }else{
        x = 0; y = 0;
    }

    this->initiator = initiator;
    this->ttAffected = ttAffected;
}

Animation Action::getAnimation(){ return animation; }
int Action::getX(){ return x; }
int Action::getY(){ return y; }

Initiator Action::getInitiator(){ return initiator; }

TileType Action::getTtAffected(){ return ttAffected; }

void Action::setY(int y){
    if(y>=0) this->y = y;
}

void Action::setTtAffected(TileType tt){
    this->ttAffected = tt;
}

