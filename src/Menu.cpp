#include "Menu.hpp"
#include <iostream>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

Menu::Menu(){
    Window window = Window();
    title = Title(window.getCenterX(), window.getCenterY());
}
Menu::Menu(Window window){
    title = Title(window.getCenterX(), window.getCenterY());
};
void Menu::printTitle(){
    move(title.getNWy(), title.getNWx());
    for(int i=0; i<title.getHeight(); i++){
        printw(title.getTitleString(i));
        move(title.getNWy()+(i+1), title.getNWx());
    }
}
void Menu::printStartScreen(Window window){
    clear();
    printTitle();
    window.printFrame();
    curs_set(0);
    sleep(3);
    mvprintw(title.getNWy() + title.getHeight() + 1, title.getNWx() , "Press space to enter the Menu");
    refresh();
}

void Menu::printMenu() {
    clear();
    mvprintw(0,0, "B2DAP");
    mvprintw(2,0, "1. PLAY");
    mvprintw(3,0, "0. QUIT");
    refresh();
}

void Menu::printEndScreen() {
    mvprintw(0, 0, "Bon Voyage");
    refresh();
    option = MenuOption::EXIT;
    sleep(2);
    system("reset");
}

void Menu::initGame() {
    mvprintw(0, 0, "The Game starts");
    refresh();
    sleep(1);
    mvprintw(1, 0, "freak bitches");
    refresh();
    option = MenuOption::PLAY;
}

void Menu::menuLoop(Window window) {
    char choice;
    printStartScreen(window);
    do{
        move(window.getHeight()-1, window.getWidth()-1);
        choice = getch();
    }while(choice != ' ');
    choice = '_';

    while (choice != '0' && choice != '1') {
        printMenu();
        choice = getch();
    }

    clear();
    switch (choice) {
    case '0':
        printEndScreen();
        break;

    case '1':
        initGame();
        break;

    default:
        cout << "you're not supposed to be here";

    }
    sleep(3);
}

MenuOption Menu::getOption() { return option; }

