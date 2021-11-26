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
	hero = Hero(1,h-1,100,50);
    currentLevel = 0;
}

void Game::draw(bool newLevel){
	if(newLevel) clear();
	//as of now, it draws terrain elements and the hero
	
	//hero drawing
	drawHero();

	//terrain drawing
	int x,y;
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
}

void Game::drawHero(){
	int x=0, y=0;
	hero.getXY(x,y);

	//this should hide the previous' hero's position with a ' ' char
	if(hero.getDirection() != Direction::STILL){
		switch(hero.getDirection()){
			case Direction::LEFT:
			mvaddch(y, x+1, ' ');
			break;

			case Direction::RIGHT:
			mvaddch(y, x-1, ' ');
			break;

			//all other direction cases
		}
	}
	
	mvaddch(y, x, hero.getTileChar());

}

void Game::input(){
	nodelay(stdscr, TRUE);
	noecho();

	int x, y;
	hero.getXY(x,y);

	char action = '_';
	if((action = getch()) != ERR){
		switch(action){
			case 'w':
			//maybe we can have the hero climb up a ladder
			break;

			case 'a':
			if(x>0 && x <= window.getWidth()) {
				hero.setXY(x-1, y);
				hero.setDirection(Direction::LEFT);
			}
			break;
			
			case 's':
			//climb down a ladder or no use
			break;
			
			case 'd':
			if(x>=0 && x < window.getWidth()) {
				hero.setXY(x+1, y);
				hero.setDirection(Direction::RIGHT);
			}
			break;
			
			case ' ':
			//code for having the hero jump
			break;

			case 'x':
			gameOver = true;
			//still needs overarching loop to detect the gameover and redirect to the main menu
			break;

			case 'p':
			//here code to stop all moving entities 
			//and to display some sort of PAUSE label somewhere
			hero.setDirection(Direction::STILL);
			break;

			default:
			hero.setDirection(Direction::STILL);

		}
	}

}

void Game::logic(){
	//some collision detection code to avoid having the hero pass through other objects
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

		bool newLevel = true;
		while(!gameOver){
			//if(levelChanged) newLevel = true;
			draw(newLevel);
			input();
			newLevel = false;
		}
	}

	endwin();
}

Menu Game::getMenu(){ return menu; }