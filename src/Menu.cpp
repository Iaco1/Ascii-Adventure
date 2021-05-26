#include "Menu.hpp"
#include <iostream>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

Menu::Menu(){
    windowWidth = WINDOW_WIDTH;
    windowHeight = WINDOW_HEIGHT;
    title = "Project-X";
    for(titleWidth = 0; title[titleWidth]!='\0'; titleWidth++);
    titleHeight = 1;
};
void Menu::printTitle(int x, int y){
    move(y,x);
    printw(title);
}
void Menu::printStartScreen(char &choice){
    clear();
    printTitle(windowWidth/2 - titleWidth/2, windowHeight/2 - titleHeight/2);
    printFrame();
    curs_set(0);    
    sleep(3);
    mvprintw(windowHeight/2 - titleHeight/2 + 2, windowWidth/2 - titleWidth/2, "Press 1 to enter the Menu");
    refresh();
}
void Menu::printFrame(){
    const char frameChar1 = '-', frameChar2 = ':';
    for(int i=0; i <= windowWidth; i++) {
        mvaddch(0,i,frameChar1);
        mvaddch(windowHeight,i,frameChar1);
        refresh();
    }
    for(int i=1; i<=windowHeight-1; i++){
        mvaddch(i, 0, frameChar2);
        mvaddch(i, windowWidth, frameChar2);
        refresh();
    }
    move(windowHeight, windowWidth);
    refresh();
}
void Menu::printMenu(){
    clear();
    mvprintw(0,0, "Project-X");
    mvprintw(2,0, "1. PLAY");
    mvprintw(3,0, "0. QUIT");
    refresh();
}
void Menu::printEndScreen(){
    mvprintw(0,0, "Bon Voyage");
            refresh();
	        sleep(2);
	        system("reset");
}
void Menu::initGame(){
    mvprintw(0,0, "The Game starts");
            refresh();
            sleep(1);
            mvprintw(1,0, "freak bitches");
            refresh();
}
void Menu::menuLoop(){
    char choice;
    printStartScreen(choice);
    do{
        move(windowHeight-1, windowWidth-1);
        choice = getch();
    }while(choice != '1');
    choice = ' ';

    while(choice != '0' && choice != '1'){
        printMenu();
        choice = getch();
    }

    clear();
    switch(choice){
        case '0':
	        printEndScreen();
            break;

        case '1':
            initGame();
            break;
        
        default:
            cout<<"you're not supposed to be here";
    }
        sleep(3);
}
