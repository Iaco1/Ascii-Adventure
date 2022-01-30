#pragma once
#include "Entity.hpp"

enum class EnemyType{ SENTRY, BOMBER, SIZE};

/*
    this class describes the EnemyType of the in-game enemies
    each EnemyType has a different on-screen representation
*/
class Enemy : public Entity{
    private:
    EnemyType et;

    public:
    Enemy();
    Enemy(int x, int y, int hp, int dp, EnemyType et);
    char getTileChar();
};