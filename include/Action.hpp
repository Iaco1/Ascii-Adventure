#pragma once
#include <chrono>
#include "Object.hpp"

enum class Animation{CLIMB_UP, CLIMB_DOWN, LEFT, RIGHT, STILL, JUMPING, FALLING, QUIT, PAUSE, SHOOTING};
enum class Initiator{ USER, LOGIC, ENEMY_PATTERN};

/*
this class describes an interaction that was carried out by an entity in the map
- Each animation corresponds to a key that can be pressed, except for some unimplemented ones
- the coordinates refer to the position of the affected TileType or element of the map
- the initiator is the author of the action: 
    if the user presses 'a' and the hero moves left, initiator is Initiator::USER
    if the user walks over a ledge he will fall and the initator for the action of falling will be Initiator::LOGIC
    if an enemy moves and is not falling his movements are handled by a movement method and the initiator is Initiator::ENEMY_PATTERN
- the ttAffected indicates which element of the map was affected by the action
- the delay is used to slow down certain movements so that the user can see them.
  It corresponds to the number of TileType::STILL actions that the entity will have imposed upon itself
*/
class Action{
    protected:
    Animation animation;
    int x, y; //affected position
    Initiator initiator; // USER || LOGIC
    TileType ttAffected; //amongst the (possibly) many tiletypes there could be in the same position
    int delay;  // the unit is no. of actions in the action log

    public:
    Action();
    Action(Animation animation, int x, int y, Initiator initiator, TileType ttAffected, int delay);
    Animation getAnimation();
    int getX();
    int getY();
    Initiator getInitiator();
    TileType getTtAffected();
    void setY(int y);
    void setTtAffected(TileType tt);
    void setXY(int x, int y);
    void setAnimation(Animation animation);
    void setInitiator(Initiator initiator);
    int getDelay();
    void setDelay(int delay);
};