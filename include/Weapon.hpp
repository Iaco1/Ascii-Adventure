#pragma once

enum class WeaponType{ HANDGUN};

class Weapon{
    protected:
    WeaponType weaponType;
    int dp; //damage points per shot
    int maxAmmo;
    int magazineAmmo;
    
    public:
    Weapon();
    Weapon(int dp, int maxAmmo, int magazineAmmo, WeaponType weaponType);
    const char* weaponTypeToStr();
    int getMaxAmmo();
    int getMagazineAmmo();
    int getDp();
    void setMagazineAmmo(int magazineAmmo);

};