#include "Window.hpp"
#include "Title.hpp"

enum class MenuOption{ PLAY, EXIT };

class Menu{
    protected:
    Window window;
    Title title;
    MenuOption option;

public:
    Menu();
    Menu(int w, int h);
    void printTitle(); //prints the titleString at the center of the window 
    void printStartScreen();
    void menuLoop();
    void printFrame();
    void printMenu();
    void printEndScreen();
    void initGame();
    MenuOption getOption();
};