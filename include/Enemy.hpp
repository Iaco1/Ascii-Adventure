#pragma once
#include "Entity.hpp"

enum class EnemyType{ SENTRY, BOMBER, SIZE};

class Enemy : public Entity{
    private:
    EnemyType et;

    public:
    Enemy();
    Enemy(int x, int y, int hp, int dp, EnemyType et);
    char getTileChar();
};