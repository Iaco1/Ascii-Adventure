#include "Menu.hpp"
#include <iostream>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

Menu::Menu(){
    
}

WINDOW* Menu::printStartScreen(){
    int title_w = 24;
    int h, w;
    getmaxyx(stdscr, h, w);
    WINDOW* title = newwin(3, title_w+2, (h/2)-3,w/2 - title_w/2);
    //wborder(title, '|','|','-','-','+','+','+','+');
    WINDOW* belowTitle = newwin(3,30+2, h-4,w/2-16); // used to write the press space to play
    //wborder(belowTitle, '|','|','-','-','+','+','+','+');
    
    mvwprintw(title,1,1, "Basic 2D ASCII Platform");
    wrefresh(title);
    
    curs_set(0);
    sleep(2);

    w = getmaxx(belowTitle);
    mvwprintw(belowTitle, 1, 1, "Press space to enter the Menu");
    wrefresh(belowTitle);

    return belowTitle;
}

void Menu::printMenu() {
    clear();
    mvprintw(0,0, "B2DAP");
    mvprintw(1,0, "1. PLAY");
    mvprintw(2,0, "0. QUIT");
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
    mvprintw(getmaxy(stdscr)/2, getmaxx(stdscr)/2-8, "The Game starts");
    refresh();
    sleep(1);
    mvprintw(getmaxy(stdscr)/2+1, getmaxx(stdscr)/2-18, "We wish for you to have a good time");
    refresh();
    sleep(1);
    option = MenuOption::PLAY;
}

void Menu::menuLoop() {
    char choice;
    WINDOW* bt = printStartScreen();
    do{
        
        choice = wgetch(bt);
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

