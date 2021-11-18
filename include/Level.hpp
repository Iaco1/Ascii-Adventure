#include "Hero.hpp"
#include "LinkedList.hpp"

const char tileChar[]{ ' ', '#', 'H', 'E', 'B', 'M' };

class Level{
    protected:
    LinkedList <Object> terrain;
    LinkedList <Entity> enemies;
    LinkedList <Entity> bonuses;
    LinkedList <Entity> maluses;
    Hero hero;
    
    public:
    Level();
    Level(int w, int h); //creates a level randomly
};