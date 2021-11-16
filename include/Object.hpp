#include "LinkedList.hpp"
enum class TileType{ EMPTY, TERRAIN, HERO, ENEMY, BONUS, MALUS, SIZE};
const char* TileTypeStr[] = {"Empty", "Terrain", "Hero", "Enemy", "Bonus", "Malus"};

class Object{
    protected:
    int x, y;
    TileType tiletype;
    
    public:
    Object();
    Object(int x, int y, TileType tiletype);
    Object(bool random); //creates a random object
    void toString(char str[24]);
};