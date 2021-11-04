#include "Object.hpp"

enum class Direction{NORTH, SOUTH, WEST, EAST, STILL};

class Entity : public Object{
    protected:
    Direction direction;
    int hp; //health points
    int speed;
    int basicAttackDP; //Damage points
    public:
    Entity();
    Entity(int x, int y, TileType tiletype, Direction direction, int hp, int speed, int basicAttackDP);

};