#include "Game.hpp"
#include "LinkedList.hpp"
#include <iostream>
#include <ncurses.h>

using namespace std;

/* NCURSES TYPICAL USAGE
initscr();
	printw("HELLO");
	refresh();
	getch();
	endwin();
*/

Game::Game() {
	gameOver = false;
	score = 0;
}

void Game::mainLoop() {
	srand(time(NULL));

	initscr();

	int w, h;
	getmaxyx(stdscr, h, w);
	w-=2;h-=2; //adjusts the size of the screen to include the borders being drawn
	
	menu = Menu(w, h);
	menu.menuLoop();

	if(menu.getOption() == MenuOption::PLAY){
		getmaxyx(stdscr, h, w);
		//map = Map(w,h);
		LinkedList<Level> list;
		list.pushTail(Level(w,h));
		list.pushTail(Level(w,h));
	}

	endwin();
}

Menu Game::getMenu(){ return menu; }