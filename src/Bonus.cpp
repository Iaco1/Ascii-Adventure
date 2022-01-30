#include "Bonus.hpp"

Bonus::Bonus(){}

Bonus::Bonus(int x, int y, int hp, BonusType bt, int quantity) : Item(x,y,TileType::BONUS, hp, 0){
    this->bt = bt;
    this->quantity = quantity;
}

//on-screen representation of each BonusType bonus
char Bonus::getTileChar(){
    char bonusChar[]{ '+', 'a', 'A', 'K'};
    return bonusChar[(int)bt];
}

//gives effect to the bonuses the player has picked up
void Bonus::giveBonus(Hero *hero){
    switch(bt){
        case BonusType::HP:{
            hero->setHp(hero->getHp() + quantity);
            break;
        }
        case BonusType::AMMO:{
            hero->getWeapon()->setMagazineAmmo(hero->getWeapon()->getMagazineAmmo() + quantity);
            break;
        }
        case BonusType::MAXAMMO:{
            hero->getWeapon()->setMaxAmmo(hero->getWeapon()->getMaxAmmo() + quantity);
            break;
        }
        case BonusType::INSTAKILL:{
            hero->getWeapon()->setDp(hero->getWeapon()->getDp()*9000);
            hero->getWeapon()->setInstakill(1);
            break;
        }
        default:
        break;

    }
    quantity = 0;
    hp = 0;
}

