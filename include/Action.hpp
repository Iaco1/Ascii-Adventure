#pragma once
#include <chrono>
#include "Object.hpp" //or could include a file contaning the enum class TileType

enum class Animation{CLIMB_UP, CLIMB_DOWN, LEFT, RIGHT, STILL, JUMPING, FALLING, QUIT, PAUSE, SHOOTING};
enum class Initiator{ USER, LOGIC, ENEMY_PATTERN};

class Action{
    protected:
    Animation animation;
    int x, y; //affected position
    Initiator initiator; // USER || LOGIC
    //Entity agent;
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