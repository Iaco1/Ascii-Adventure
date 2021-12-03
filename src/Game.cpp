#include "Game.hpp"
#include <iostream>
#include <ncurses.h>
#include <chrono>
#include <thread>

using namespace std;

const int JUMP_HEIGHT = 4;
const int targetFrameRate = 60;
auto frameDelay =  std::chrono::seconds(1/targetFrameRate); //max duration for a frame

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
	if(hero.getActionLog()[0].getAnimation() == Animation::JUMPING || hero.getActionLog()[0].getAnimation() == Animation::FALLING) std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Game::drawHero(){
	int x=0, y=0;
	hero.getXY(x,y);

	//this should hide the previous' hero's position with a ' ' char
	if(hero.getActionLog()[0].getAnimation() != Animation::STILL){
		switch(hero.getActionLog()[0].getAnimation()){
			case Animation::LEFT:
			mvaddch(y, x+1, ' ');
			break;

			case Animation::RIGHT:
			mvaddch(y, x-1, ' ');
			break;

			case Animation::CLIMB_DOWN:
			//yet to decide a stairs character
			break;

			case Animation::FALLING:
			mvaddch(y-1,x,' ');
			break;

			case Animation::CLIMB_UP:
			break;

			case Animation::JUMPING:
			mvaddch(y+1, x, ' ');
			break;

			case Animation::STILL:
			default:
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

	Animation proposedAnimation = Animation::STILL;
	Initiator proposedInitiator = Initiator::LOGIC;
	
	char userKey = '_';
	
	if((userKey = getch()) != ERR){
		switch(userKey){
			case 'w':
			//maybe we can have the hero climb up a ladder
			proposedAnimation = Animation::CLIMB_UP;
			break;

			case 'a':
			proposedAnimation = Animation::LEFT;
			break;
			
			case 's':
			//climb down a ladder or no use
			proposedAnimation = Animation::CLIMB_DOWN;
			break;
			
			case 'd':
			proposedAnimation = Animation::RIGHT;
			break;
			
			case ' ':
			//code for having the hero jump
			proposedAnimation = Animation::JUMPING;
			break;

			case 'x':
			gameOver = true;
			//still needs overarching loop to detect the gameover and redirect to the main menu
			break;

			case 'p':
			//here code to stop all moving entities 
			//and to display some sort of PAUSE label somewhere
			proposedAnimation = Animation::STILL;
			break;

			default:
			proposedAnimation = Animation::STILL;

		}
		proposedInitiator = Initiator::USER;
	}

	//keep jumping till you reached JUMP_HEIGHT even if the user presses left or right keys to jump diagonally
	// (the user initiated a jump some time ago && the hero din't move JUMP_HEIGHT units up yet) && (the user didn't ask to make a new move yet)
	if(
		(
			hero.countMoves(Animation::JUMPING, Initiator::LOGIC) < JUMP_HEIGHT-1
			&& hero.countMoves(Animation::JUMPING, Initiator::USER) >= 1
		)
		&& proposedAnimation == Animation::STILL
	){
		if(hero.countMoves(Animation::JUMPING) < JUMP_HEIGHT) {
			proposedAnimation = Animation::JUMPING;
			proposedInitiator = Initiator::LOGIC;
		}else proposedAnimation = Animation::FALLING; // this line may be superfluous
	}

	//falling mechanic
	if(proposedAnimation == Animation::STILL && map[currentLevel].elementAt(hero.getX(), hero.getY()+1) == TileType::EMPTY){
		proposedAnimation = Animation::FALLING;
		proposedInitiator = Initiator::LOGIC;
	}
	
	//sets the coordinates in which the action will take place and the time delay for it
	Action proposedAction;
	switch(proposedAnimation){
		case Animation::LEFT:
		proposedAction = Action(proposedAnimation, hero.getX()-1, hero.getY(), AnimationDelay::LEFT, proposedInitiator);
		break;

		case Animation::RIGHT:
		proposedAction = Action(proposedAnimation, hero.getX()+1, hero.getY(), AnimationDelay::RIGHT, proposedInitiator);
		break;

		case Animation::JUMPING:
		proposedAction = Action(proposedAnimation, hero.getX(), hero.getY()-1, AnimationDelay::JUMPING, proposedInitiator);
		break;

		case Animation::FALLING:
		proposedAction = Action(proposedAnimation, hero.getX(), hero.getY()+1, AnimationDelay::FALLING, proposedInitiator);
		break;

		case Animation::CLIMB_UP:
		case Animation::CLIMB_DOWN:
		case Animation::STILL:
		default:
		proposedAction = Action(proposedAnimation, hero.getX(), hero.getY(), AnimationDelay::STILL, proposedInitiator);
		
	}

	
	return proposedAction;

}

void Game::logic(Action proposedAction){
	Action engagedAction;

	//enstablishes the legality of the action
	switch(proposedAction.getAnimation()){
		case Animation::CLIMB_UP:
		break;

		case Animation::CLIMB_DOWN:
		break;

		case Animation::JUMPING:
		if(hero.getY()>0 && hero.getY() <= window.getHeight()){
			if(map[currentLevel].elementAt(hero.getX(), hero.getY()-1) == TileType::EMPTY){
				if(hero.countMoves(Animation::JUMPING) < JUMP_HEIGHT){
					hero.setXY(hero.getX(), hero.getY()-1);
					engagedAction = proposedAction;
				}
			}
		}
		break;

		case Animation::LEFT:
		if(hero.getX()>0 && hero.getX() <= window.getWidth()) {
			if(map[currentLevel].elementAt(hero.getX()-1, hero.getY()) == TileType::EMPTY){
				hero.setXY(hero.getX()-1, hero.getY());
				engagedAction = proposedAction;
			}
		}
		break;

		case Animation::RIGHT:
		if(hero.getX()>=0 && hero.getX() < window.getWidth()) {
			if(map[currentLevel].elementAt(hero.getX()+1, hero.getY()) == TileType::EMPTY){
				hero.setXY(hero.getX()+1, hero.getY());
				engagedAction = proposedAction;
			}
		}
		break;

		case Animation::FALLING:
		if(hero.getY() >= 0 && hero.getY() < window.getHeight()){
			switch(map[currentLevel].elementAt(hero.getX(), hero.getY()+1))
			{
				case TileType::EMPTY:
				hero.setXY(hero.getX(), hero.getY()+1);
				engagedAction = proposedAction;
				break;

				case TileType::TERRAIN:
				engagedAction = Action(Animation::STILL, hero.getX(), hero.getY(), AnimationDelay::STILL, Initiator::LOGIC);
				break;

				case TileType::BONUS:
				case TileType::MALUS:
				case TileType::ENEMY:
				case TileType::HERO:
				case TileType::SIZE:
				default:
				break;
			}
		}
		break; 

		case Animation::STILL:
		default: // this if may be useless
		if(hero.getActionLog()[0].getAnimation() == Animation::FALLING && map[currentLevel].elementAt(hero.getX(), hero.getY()+1) == TileType::EMPTY){ 
			hero.setXY(hero.getX(), hero.getY()+1);
			engagedAction = Action(Animation::FALLING, hero.getX(), hero.getY(), AnimationDelay::FALLING, Initiator::LOGIC);
		}else engagedAction = proposedAction;
	}

	hero.registerMove(engagedAction);
	
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