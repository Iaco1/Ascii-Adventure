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

void Game::createMap(){
	//here we genereate levels and the hero
	int w = window.getWidth(), h = window.getHeight();

    map.pushHead(new Node<Level>(Level(w,h)));
	hero = Hero(1,h-1,100,0,100);
    currentLevel = 0;
}

void Game::draw(){
	clear();

	//as of now, it draws terrain elements and the hero
	//hero drawing
	int x=0, y=0;
	hero.getXY(x,y);
	mvaddch(y, x, hero.getTileChar());

	//terrain drawing
	for(int i=0; i<map[currentLevel].getTerrain().getSize(); i++){
		map[currentLevel].getTerrain()[i].getXY(x,y);
		mvaddch(y, x, map[currentLevel].getTerrain()[i].getTileChar());
	}
	//enemies drawing
	//...
	//bonuses drawing
	//...
	//maluses drawing
	//...

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

		createMap();
		draw();
	}

	endwin();
}

Menu Game::getMenu(){ return menu; }