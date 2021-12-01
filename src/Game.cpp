#include "Game.hpp"
#include <iostream>
#include <ncurses.h>
#include <chrono>
#include <thread>

using namespace std;

const int JUMP_HEIGHT = 4;
const int targetFrameRate = 60;
auto frameDelay =  std::chrono::seconds(1/targetFrameRate);

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
	if(hero.getPrevMovements()[0] == Action::JUMPING || hero.getPrevMovements()[0] == Action::FALLING) std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Game::drawHero(){
	int x=0, y=0;
	hero.getXY(x,y);

	//this should hide the previous' hero's position with a ' ' char
	if(hero.getAction() != Action::STILL){
		switch(hero.getAction()){
			case Action::LEFT:
			mvaddch(y, x+1, ' ');
			break;

			case Action::RIGHT:
			mvaddch(y, x-1, ' ');
			break;

			case Action::CLIMB_DOWN:
			//yet to decide a stairs character
			break;

			case Action::FALLING:
			mvaddch(y-1,x,' ');
			break;

			case Action::CLIMB_UP:
			break;

			case Action::JUMPING:
			mvaddch(y+1, x, ' ');
			break;
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

Action Game::input(){
	nodelay(stdscr, TRUE);
	noecho();

	Action proposedAction = Action::STILL;
	
	char action = '_';
	if(hero.getPrevMovements()[0] == Action::JUMPING){
		if(hero.countMoves(Action::JUMPING) < JUMP_HEIGHT) proposedAction = Action::JUMPING;
		else proposedAction = Action::FALLING;
	}
	else if((action = getch()) != ERR){
		switch(action){
			case 'w':
			//maybe we can have the hero climb up a ladder
			proposedAction = Action::CLIMB_UP;
			break;

			case 'a':
			proposedAction = Action::LEFT;
			break;
			
			case 's':
			//climb down a ladder or no use
			proposedAction = Action::CLIMB_DOWN;
			break;
			
			case 'd':
			proposedAction = Action::RIGHT;
			break;
			
			case ' ':
			//code for having the hero jump
			proposedAction = Action::JUMPING;
			break;

			case 'x':
			gameOver = true;
			//still needs overarching loop to detect the gameover and redirect to the main menu
			break;

			case 'p':
			//here code to stop all moving entities 
			//and to display some sort of PAUSE label somewhere
			proposedAction = Action::STILL;
			break;

			default:
			proposedAction = Action::STILL;

		}
	}
	return proposedAction;

}

void Game::logic(Action proposedAction){
	//some collision detection code to avoid having the hero pass through other objects
	int x, y;
	hero.getXY(x,y);

	switch(proposedAction){
		case Action::CLIMB_UP:
		break;

		case Action::CLIMB_DOWN:
		break;

		case Action::JUMPING:
		if(y>0 && y <= window.getHeight()){
			if(map[currentLevel].elementAt(x,y-1) == TileType::EMPTY){
				if(hero.countMoves(Action::JUMPING) < JUMP_HEIGHT){
					hero.setXY(x, y-1);
					hero.setAction(Action::JUMPING);
				}
			}
		}
		break;

		case Action::LEFT:
		if(x>0 && x <= window.getWidth()) {
			if(map[currentLevel].elementAt(x-1, y) == TileType::EMPTY){
				hero.setXY(x-1, y);
				hero.setAction(Action::LEFT);
			}
		}
		break;

		case Action::RIGHT:
		if(x>=0 && x < window.getWidth()) {
			if(map[currentLevel].elementAt(x+1,y) == TileType::EMPTY){
				hero.setXY(x+1, y);
				hero.setAction(Action::RIGHT);
			}
		}
		break;

		case Action::FALLING:
		if(y>=0 && y< window.getHeight()){
			switch(map[currentLevel].elementAt(x,y+1))
			{
				case TileType::EMPTY:
				hero.setXY(x,y+1);
				hero.setAction(Action::FALLING);
				break;

				case TileType::TERRAIN:
				hero.setAction(Action::STILL);
				break;
			}
		}
		break; 

		case Action::STILL:
		default:
		if(hero.getAction() == Action::FALLING && map[currentLevel].elementAt(x, y+1) == TileType::EMPTY){ 
			hero.setXY(x, y+1);
			hero.setAction(Action::FALLING);
		}else hero.setAction(Action::STILL);
	}
	hero.registerMove(hero.getAction());
	
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
			using namespace std::chrono;

			time_point<system_clock> frameStart;
			duration<double> frameTime; // frameTime indicates how much time the current frame has taken
			frameStart = system_clock::now();
			
			//if(levelChanged) newLevel = true;
			draw(newLevel);
			logic(input());
			newLevel = false;

			frameTime = system_clock::now() - frameStart;
			
			if(frameDelay > frameTime){
				std::this_thread::sleep_for(frameDelay - frameTime);
			}

			
		}
	}

	endwin();
}

Menu Game::getMenu(){ return menu; }