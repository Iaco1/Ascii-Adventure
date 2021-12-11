#include "Entity.hpp"
#include "Weapon.hpp"

class Hero : public Entity{
    protected:
    Weapon weapon;

    public:
    Hero();
    Hero(int x, int y, int hp, int basicAttackDP, Weapon weapon);
    Weapon* getWeapon();
    
};