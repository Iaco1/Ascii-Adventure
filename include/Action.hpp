#pragma once
#include <chrono>
#include "Object.hpp" //or could include a file contaning the enum class TileType

enum class Animation{CLIMB_UP, CLIMB_DOWN, LEFT, RIGHT, STILL, JUMPING, FALLING, QUIT, PAUSE, SHOOTING};
enum class Initiator{ USER, LOGIC};

class Action{
    protected:
    Animation animation;
    int x, y; //affected position
    Initiator initiator;
    TileType ttAffected; //amongst the (possibly) many tiletypes there could be in the same position

    public:
    Action();
    Action(Animation animation, int x, int y, Initiator initiator, TileType ttAffected);
    Animation getAnimation();
    int getX();
    int getY();
    Initiator getInitiator();
    TileType getTtAffected();
};