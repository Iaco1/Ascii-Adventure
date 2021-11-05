#include "LinkedList.hpp"
enum class TileType{ EMPTY, TERRAIN, HERO, ENEMY, BONUS, MALUS};
const char* TileTypeStr[] = {"Empty", "Terrain", "Hero", "Enemy", "Bonus", "Malus"};

class Object{
    protected:
    int x, y;
    TileType tiletype;
    
    public:
    Object();
    Object(int x, int y, TileType tiletype);
    void toString(char str[24]);
};