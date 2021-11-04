#include "LinkedList.hpp"
enum class TileType{ EMPTY, TERRAIN, HERO, ENEMY, BONUS, MALUS};

class Object{
    protected:
    int x, y;
    TileType tiletype;
    
    public:
    Object();
    Object(int x, int y, TileType tiletype);
};