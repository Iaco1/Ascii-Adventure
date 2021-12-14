#include "Action.hpp"

enum class Direction{ LEFT, RIGHT};

const int SIGNIFICANT_MOVES = 8;

class Entity : public Object{
    protected:
    Action actionLog[SIGNIFICANT_MOVES];
    int hp; //health points
    int basicAttackDP; //Damage points
    Direction direction; //where the "head" of the entity is pointing to, useful for attack purposes
    
    public:
    Entity();
    Entity(int x, int y, TileType tileType, int hp, int basicAttackDP, Direction direction);
    bool isMovementAction(Action action);

    void registerMove(Action action);
    int countMoves(Action action);
    int countMoves(Animation animation);
    int countMoves(Animation animation, Initiator initiator);
    Action* getActionLog();
    int getHp();
    void setHp(int hp);
    Direction getDirection();
};