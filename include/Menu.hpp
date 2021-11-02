#include "Window.hpp"
#include "Title.hpp"
class Menu{
    protected:
    Window window;
    Title title;

public:
    Menu();
    void printTitle(); //prints the titleString at the center of the window 
    void printStartScreen();
    void menuLoop();
    void printFrame();
    void printMenu();
    void printEndScreen();
    void initGame();
};