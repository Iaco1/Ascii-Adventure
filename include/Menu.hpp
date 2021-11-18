#include "Window.hpp"
#include "Title.hpp"

enum class MenuOption{ PLAY, EXIT };

class Menu{
    protected:
    Title title;
    MenuOption option;

public:
    Menu();
    Menu(Window window);
    void printTitle(); //prints the titleString at the center of the window 
    void printStartScreen(Window window);
    void menuLoop(Window window);
    void printFrame(Window window);
    void printMenu();
    void printEndScreen();
    void initGame();
    MenuOption getOption();
};