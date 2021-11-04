#include "Entity.hpp"

class Hero : public Entity{
    protected:
    public:
    Hero();
    Hero(int x, int y, TileType tiletype, Direction direction, int hp, int speed, int basicAttackDP);
};