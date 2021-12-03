#include "Action.hpp"

Action::Action(){
    animation = Animation::STILL;
    x=0; y=0;
    delay = std::chrono::milliseconds(0);
    initiator = Initiator::LOGIC;
}

Action::Action(Animation animation, int x, int y, AnimationDelay ec_delay, Initiator initiator){
    this->animation = animation;
    
    if(x>=0 && y>=0){
        this->x = x;
        this->y = y;
    }else{
        x = 0; y = 0;
    }
    int i_delay = static_cast<int>(ec_delay);

    if(!(i_delay >= 0 && i_delay < 1000)) i_delay = 0;
    this->delay = std::chrono::milliseconds(i_delay);

    this->initiator = initiator;
}
Action::Action(Animation animation, int x, int y, int delay, Initiator initiator){
    this->animation = animation;
    
    if(x>=0 && y>=0){
        this->x = x;
        this->y = y;
    }else{
        x = 0; y = 0;
    }

    if(!(delay >= 0 && delay < 1000)) delay = 0;
    this->delay = std::chrono::milliseconds(delay);

    this->initiator = initiator;
}
Animation Action::getAnimation(){ return animation; }
int Action::getX(){ return x; }
int Action::getY(){ return y; }

int Action::getDelay(){ return delay.count(); }

Initiator Action::getInitiator(){ return initiator; }

