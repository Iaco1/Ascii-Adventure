#include "Game.hpp"
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

void Game::draw(){
	clear();
	window.printFrame();
	mvprintw(5,5,"X");
	refresh();
	getch();
}

void Game::mainLoop() {
	srand(time(NULL));

	initscr();

	int w, h;
	getmaxyx(stdscr, h, w);
	window = Window(w,h);

	menu = Menu(window);
	menu.menuLoop(window);

	if(menu.getOption() == MenuOption::PLAY){
		getmaxyx(stdscr, h, w);
		window = Window(w,h);

		map = Map(w,h);
		draw();
	}

	endwin();
}

Menu Game::getMenu(){ return menu; }