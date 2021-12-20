#include "Entity.hpp"
#include "Weapon.hpp"

class Hero : public Entity{
    protected:
    Weapon weapon;
    int maxHp;

    public:
    Hero();
    Hero(int x, int y, int hp, int basicAttackDP, Weapon weapon);
    Weapon* getWeapon();
    int getMaxHp();
    void setMaxHp(int maxHp);
    void setHp(int hp);
};