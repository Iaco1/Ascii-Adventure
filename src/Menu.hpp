class Menu{
    protected:
    int windowWidth, windowHeight;
    const char *title;
    int titleWidth, titleHeight;

    public:
    Menu();
    void printTitle(int x, int y);
    void printStartScreen(char &choice);
    void menuLoop();
    void printFrame();
    void printMenu();
    void printEndScreen();
    void initGame();
};