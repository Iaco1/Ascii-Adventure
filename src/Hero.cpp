#include "Hero.hpp"

Hero::Hero(){}
Hero::Hero(int x, int y, int hp, int basicAttackDP) : Entity(x,y, TileType::HERO, Action::STILL, hp, basicAttackDP){
    for(int i=0; i<SIGNIFICANT_MOVES; i++){
        prevMovements[i] = Action::STILL;
    }
}

//registers last 6 actions by inserting the last one in prevMovements[0] and deleting the oldest one in prevMovements[SIGNIFICANT_MOVES-1]
void Hero::registerMove(Action action){
    if(isMovementAction(action)){
        for(int i = SIGNIFICANT_MOVES-1; i>0; i--){
            prevMovements[i] = prevMovements[i-1]; 
        }
        prevMovements[0] = action;
    }
}

//counts the no. of nodes that have matching data 
int Hero::countMoves(Action action){
	int count = 0;
	for(int i=0; i<SIGNIFICANT_MOVES-1; i++){
        if(prevMovements[i] == action) count++;
    }
	return count;
}

Action* Hero::getPrevMovements(){
    Action* p = prevMovements;
    return p;
}