#pragma once
#include <ncurses.h>
#include <panel.h>

enum class MenuOption{ PLAY, EXIT };

class Menu{
    protected:
    MenuOption option;

public:
    Menu();
    WINDOW* printStartScreen();
    void menuLoop();
    void printMenu();
    void printEndScreen();
    void initGame();
    void printHelpScreen();
    MenuOption getOption();
};