#include "Weapon.hpp"

const int MAXDP = 100;
const int MAX_MAXAMMO = 20;

Weapon::Weapon(){}
Weapon::Weapon(int dp, int maxAmmo, int magazineAmmo, WeaponType weaponType){
    if(dp>0 && dp<MAXDP) this->dp = dp;
    else this->dp = 30;

    if(maxAmmo > 0 && maxAmmo <= MAX_MAXAMMO) this->maxAmmo = maxAmmo;
    else this->maxAmmo = 10;

    if(magazineAmmo >0 && magazineAmmo < this->maxAmmo) this->magazineAmmo = magazineAmmo;
    else this->magazineAmmo = this->maxAmmo;

    this->weaponType = weaponType;
}

const char* Weapon::weaponTypeToStr(){
    const char* gunNameStr[] = {"Handgun"};
    return gunNameStr[(int)weaponType];
}

int Weapon::getMaxAmmo(){ return maxAmmo; }
int Weapon::getMagazineAmmo(){ return magazineAmmo; }
int Weapon::getDp(){ return dp; }
void Weapon::setMagazineAmmo(int magazineAmmo){
    if(magazineAmmo <= maxAmmo && magazineAmmo >= 0) this->magazineAmmo = magazineAmmo;
}

void Weapon::setMaxAmmo(int maxAmmo){
    if(maxAmmo > 0 ) this->maxAmmo = maxAmmo;
}

void Weapon::setDp(int dp){
    if(dp>0) this->dp = dp;
}