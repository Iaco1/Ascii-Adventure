enum class TileType{ EMPTY, TERRAIN, HERO, ENEMY, BONUS, MALUS, SIZE};

class Object{
    protected:
    int x, y;
    TileType tiletype;
    
    public:
    Object();
    Object(int x, int y, TileType tiletype);
    Object(bool random); //creates a random object
    void toString(char str[24]);
    void getXY(int &x, int &y);
    char getTileChar();
    void setXY(int x, int y);
    TileType getTileType();
};