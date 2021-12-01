#include "Object.hpp"

enum class Action{CLIMB_UP, CLIMB_DOWN, LEFT, RIGHT, STILL, JUMPING, FALLING};

class Entity : public Object{
    protected:
    Action action;
    int hp; //health points
    int basicAttackDP; //Damage points
    
    public:
    Entity();
    Entity(int x, int y, TileType tiletype, Action action, int hp, int basicAttackDP);
    void setAction(Action action);
    Action getAction();
    bool isMovementAction(Action action);
};