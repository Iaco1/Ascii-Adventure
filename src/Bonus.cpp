#include "Bonus.hpp"

Bonus::Bonus(){}

Bonus::Bonus(int x, int y, int hp, BonusType bt, int quantity) : Item(x,y,TileType::BONUS, hp, 0){
    this->bt = bt;
    this->quantity = quantity;
}

char Bonus::getTileChar(){
    char bonusChar[]{ '+', 'a', 'A', 'K'};
    return bonusChar[(int)bt];
}

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
            break;
        }

    }
    quantity = 0;
    hp = 0;
}

