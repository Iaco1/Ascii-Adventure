#include "Game.hpp"
#include "Menu.hpp"
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

	Menu menu;
	menu.menuLoop();

	endwin();
}