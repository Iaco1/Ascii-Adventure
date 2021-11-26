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

	//terrain, enemies, bonuses and maluses' drawing
	drawLevelElements(map[currentLevel].getTerrain());
	drawLevelElements(map[currentLevel].getEnemies());
	drawLevelElements(map[currentLevel].getBonuses());
	drawLevelElements(map[currentLevel].getMaluses());

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
template <class T>
void Game::drawLevelElements(LinkedList<T> list){
	int x,y;
	for(int i=0; i<list.getSize(); i++){
		list[i].getXY(x,y);
		mvaddch(y, x, list[i].getTileChar());
	}
}

Direction Game::input(){
	nodelay(stdscr, TRUE);
	noecho();

	Direction proposedDirection = Direction::STILL;

	char action = '_';
	if((action = getch()) != ERR){
		switch(action){
			case 'w':
			//maybe we can have the hero climb up a ladder
			proposedDirection = Direction::CLIMB_UP;
			break;

			case 'a':
			proposedDirection = Direction::LEFT;
			break;
			
			case 's':
			//climb down a ladder or no use
			proposedDirection = Direction::CLIMB_DOWN;
			break;
			
			case 'd':
			proposedDirection = Direction::RIGHT;
			break;
			
			case ' ':
			//code for having the hero jump
			proposedDirection = Direction::JUMPING;
			break;

			case 'x':
			gameOver = true;
			//still needs overarching loop to detect the gameover and redirect to the main menu
			break;

			case 'p':
			//here code to stop all moving entities 
			//and to display some sort of PAUSE label somewhere
			proposedDirection = Direction::STILL;
			break;

			default:
			proposedDirection = Direction::STILL;

		}
	}
	return proposedDirection;

}

void Game::logic(Direction proposedDirection){
	//some collision detection code to avoid having the hero pass through other objects
	int x, y;
	hero.getXY(x,y);

	switch(proposedDirection){
		case Direction::CLIMB_UP:
		break;

		case Direction::CLIMB_DOWN:
		break;

		case Direction::JUMPING:
		break;
		
		case Direction::FALLING:
		break;

		case Direction::LEFT:
		if(x>0 && x <= window.getWidth()) {
			if(map[currentLevel].elementAt(x-1, y) == TileType::EMPTY){
				hero.setXY(x-1, y);
				hero.setDirection(Direction::LEFT);
			}
		}
		break;

		case Direction::RIGHT:
		if(x>=0 && x < window.getWidth()) {
			if(map[currentLevel].elementAt(x+1,y) == TileType::EMPTY){
				hero.setXY(x+1, y);
				hero.setDirection(Direction::RIGHT);
			}
		}
		break;

		case Direction::STILL:
		hero.setDirection(Direction::STILL);
		break;

		default:
		hero.setDirection(Direction::STILL);
	}

	
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
			logic(input());
			newLevel = false;
		}
	}

	endwin();
}

Menu Game::getMenu(){ return menu; }