#include <iostream>
#include <ncurses.h>
#include "Menu.hpp"
#include <unistd.h>

using namespace std;

/*
initscr();
	printw("HELLO FREAK BITCHES!!!");
	refresh();
	getch();
	endwin();
*/

int main(int argc, char *argv[]){
	initscr();

	Menu menu;
	menu.menuLoop();
	
	endwin();
}