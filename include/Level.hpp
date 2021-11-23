#include "Hero.hpp"
#include "LinkedList.hpp"

class Level{
    protected:
    LinkedList <Object> terrain;
    LinkedList <Entity> enemies;
    LinkedList <Entity> bonuses;
    LinkedList <Entity> maluses;
    
    public:
    Level();
    Level(int w, int h); //creates a level randomly
    LinkedList <Object> getTerrain();
    LinkedList <Entity> getEnemies();
    LinkedList <Entity> getBonuses();
    LinkedList <Entity> getMaluses();
};