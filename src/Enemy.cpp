#include "Enemy.hpp"

Enemy::Enemy(){}

Enemy::Enemy(int x, int y, int hp, int dp, EnemyType et) : Entity(x,y,TileType::ENEMY, hp, dp, Direction::RIGHT){
    if(et!=EnemyType::SIZE) this->et = et;
}

char Enemy::getTileChar(){
    char enemyChar[] = {'S', 'B'};
    return enemyChar[int(et)];
}