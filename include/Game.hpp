class Game {
protected:
    bool gameOver;
    //Map map;
    //Hero hero
    //LinkedList<Enemy> Enemies
    //LinkedList<Bonus> Bonuses
    //LinkedList<Malus> Maluses
    int score;

public:
    Game();
    void mainLoop();
    void updateMap();
    void draw();
    void input();
    void logic();
};