#include "Game.hpp"
#include "ncurses.h"
#include "Menu.hpp"
#include <iostream>
#include "LinkedList.hpp"

/* NCURSES TYPICAL USAGE
initscr();
	printw("HELLO");
	refresh();
	getch();
	endwin();
*/

Game::Game(){}
void Game::mainLoop(){
    srand(time(NULL));
	
	initscr();

	Menu menu;
	menu.menuLoop();
	
	endwin();
}