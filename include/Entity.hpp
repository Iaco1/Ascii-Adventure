#include "Object.hpp"
#include "Action.hpp"


const int SIGNIFICANT_MOVES = 8;

class Entity : public Object{
    protected:
    Action actionLog[SIGNIFICANT_MOVES];
    int hp; //health points
    int basicAttackDP; //Damage points
    
    public:
    Entity();
    Entity(int x, int y, TileType tileType, int hp, int basicAttackDP);
    bool isMovementAction(Action action);

    void registerMove(Action action);
    int countMoves(Action action);
    int countMoves(Animation animation);
    int countMoves(Animation animation, Initiator initiator);
    Action* getActionLog();
};