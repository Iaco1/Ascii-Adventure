#pragma once

enum class WeaponType{ HANDGUN};

/*
representation of a weapon of type WeaponType that inflicts a certain dp damage 
and that has magazineAmmo / maxAmmo
the flag has the purpose of removing a bonus once the hero moves in between levels
*/

class Weapon{
    protected:
    WeaponType weaponType;
    int dp; //damage points per shot
    int maxAmmo;
    int magazineAmmo;
    bool instakill;
    
    public:
    Weapon();
    Weapon(int dp, int maxAmmo, int magazineAmmo, WeaponType weaponType);
    const char* weaponTypeToStr();
    int getMaxAmmo();
    int getMagazineAmmo();
    int getDp();
    void setMagazineAmmo(int magazineAmmo);
    void setMaxAmmo(int maxAmmo);
    void setDp(int dp);
    bool instakillOn();
    void setInstakill(bool ik);

};