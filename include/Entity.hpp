#include "Object.hpp"

enum class Direction{CLIMB_UP, CLIMB_DOWN, LEFT, RIGHT, STILL, JUMPING, FALLING};

class Entity : public Object{
    protected:
    Direction direction;
    int hp; //health points
    int speed;
    int basicAttackDP; //Damage points
    
    public:
    Entity();
    Entity(int x, int y, TileType tiletype, Direction direction, int hp, int speed, int basicAttackDP);
    void setDirection(Direction direction);
    Direction getDirection();
    void setSpeed(int speed);
    int getSpeed();
};