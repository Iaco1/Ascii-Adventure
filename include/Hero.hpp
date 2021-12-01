#include "Entity.hpp"

const int SIGNIFICANT_MOVES = 8;

class Hero : public Entity{
    protected:
    Action prevMovements[SIGNIFICANT_MOVES];

    public:
    Hero();
    Hero(int x, int y, int hp, int basicAttackDP);
    void registerMove(Action action);
    int countMoves(Action action);
    Action* getPrevMovements();
};