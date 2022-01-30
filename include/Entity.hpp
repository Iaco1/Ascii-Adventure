#pragma once
#include "Action.hpp"
#include "Item.hpp"

enum class Direction{ LEFT, RIGHT};

const int SIGNIFICANT_MOVES = 60;

/*
    this class was a base class to describe both Enemies and the Hero
    it contains:
    
    - the actionLog[], an array of the last SIGNIFICANT_MOVES actions carried out by the Entity
      with order: more recent->first, older->last

    - directon, an enum class object that represents where the head of the entity is facing,
      which is useful when determining in which direction one should shoot bullets
*/

class Entity : public Item{
    protected:
    Action actionLog[SIGNIFICANT_MOVES];
    Direction direction; //where the "head" of the entity is pointing to, useful for attack purposes
    
    public:
    Entity();
    Entity(int x, int y, TileType tileType, int hp, int dp, Direction direction);
    bool isMovementAction(Action action);

    void registerMove(Action action);
    int countMoves(Action action);
    int countMoves(Animation animation, int n = SIGNIFICANT_MOVES);
    int countMoves(Animation animation, Initiator initiator, int n = SIGNIFICANT_MOVES);
    Action* getActionLog();
    Direction getDirection();
    
};