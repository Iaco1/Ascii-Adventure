#include "Game.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

using namespace std;

const int JUMP_HEIGHT = 4;
const int targetFrameRate = 60;
auto frameDelay =  std::chrono::seconds(1/targetFrameRate); //max duration for a frame


Game::Game() {
	gameOver = false;
	score = 0;
}

//inserts a newly generated level into the map and generates the hero
void Game::createMap(){
	int h, w;
	getmaxyx(levelWindow, h,w);
	h--;w--;

    map.pushHead(new Node<Level>(Level(w,h, 0)));
	hero = Hero(2,h-1,100,50, Weapon(50, 20, 20, WeaponType::HANDGUN));
    currentLevel = 0;
}

void Game::addLevel(){
	currentLevel++;
	int h, w;
	getmaxyx(levelWindow, h, w);
	h--;w--;
	map.pushTail(new Node<Level>(Level(w,h,currentLevel)));
	hero.setXY(2,h-1);
}

//handles the display of all of the level's elements and of the HUD
void Game::draw(bool changeLevel){
	if(changeLevel) {
		wclear(levelWindow);
		wrefresh(levelWindow);
		drawLevelElements(*map[currentLevel].getTerrain());
		
	}
	drawDoors();
	int HUD_h = 1;
	WINDOW* hud = newwin(HUD_h, getmaxx(levelWindow), 0, 0);
	drawHUD(hud);
	delwin(hud);
	
	//hero drawing
	drawHero();
	wrefresh(levelWindow);
	//terrain, enemies, bonuses and maluses' drawing
	
	drawLevelElements(*map[currentLevel].getEnemies());//drawEnemies();
	drawLevelElements(*map[currentLevel].getBonuses());
	drawLevelElements(*map[currentLevel].getMaluses());
	drawLevelElements(*map[currentLevel].getXps());
	drawBullets();

	wrefresh(levelWindow);
	//this slows down the refresh rate in order for the user to see certain animations
	if(getCorrespondingDelay(hero.getActionLog()[0].getAnimation()) > 0) std::this_thread::sleep_for(std::chrono::milliseconds(getCorrespondingDelay(hero.getActionLog()[0].getAnimation())));
	else if(!map[currentLevel].getBullets()->isEmpty()) std::this_thread::sleep_for(std::chrono::milliseconds(getCorrespondingDelay(Animation::SHOOTING)));
}

//draws the current hero position and hides the last one with a ' ' char
void Game::drawHero(){
	int x=0, y=0;
	hero.getXY(x,y);

	//this hides the previous' hero's position with a ' ' char
	if(hero.getActionLog()[0].getAnimation() != Animation::STILL 
	&& hero.getActionLog()[0].getTtAffected() != TileType::PL_DOOR
	&& hero.getActionLog()[0].getTtAffected() != TileType::NL_DOOR){
		switch(hero.getActionLog()[0].getAnimation()){
			case Animation::LEFT:
			mvwaddch(levelWindow, y, x+1, ' ');
			break;

			case Animation::RIGHT:
			mvwaddch(levelWindow, y, x-1, ' ');
			break;

			case Animation::CLIMB_DOWN:
			//yet to decide a stairs character
			break;

			case Animation::FALLING:
			mvwaddch(levelWindow, y-1,x,' ');
			break;

			case Animation::CLIMB_UP:
			break;

			case Animation::JUMPING:
			mvwaddch(levelWindow, y+1, x, ' ');
			break;

			case Animation::STILL:
			default:
			break;
		}
	}
	
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	wattron(levelWindow, COLOR_PAIR(2));
	mvwaddch(levelWindow, y, x, hero.getTileChar());
	wattroff(levelWindow, COLOR_PAIR(2));
}

//draws static game elements
template <class T>
void Game::drawLevelElements(LinkedList<T> list){
	int x,y;
	for(int i=0; i<list.getSize(); i++){
		list[i].getXY(x,y);
		mvwaddch(levelWindow, y, x, list[i].getTileChar());
	}
}

void Game::drawHUD(WINDOW* hud){
	mvwprintw(hud, 0,0, "HP: %d/%d - SCORE: %d - LEVEL: %d - [Weapon: %s | Ammo: %d/%d]", 
	hero.getHp(),hero.getMaxHp(), score, currentLevel, 
	hero.getWeapon()->weaponTypeToStr(), hero.getWeapon()->getMagazineAmmo(), hero.getWeapon()->getMaxAmmo());
	wrefresh(hud);
}

//draws the current bullet position and hides the previous bullet position
void Game::drawBullets(){
	int x,y;
	int prevX, nextX;
	Node<Entity>* iter = map[currentLevel].getBullets()->getHead();
	while(iter!=NULL){
		iter->data.getXY(x,y);
		if(iter->data.getDirection() == Direction::RIGHT){
			prevX = x-1;
			nextX = x+1;
		}else{
			prevX = x+1;
			nextX = x-1;
		}
		mvwaddch(levelWindow, y, prevX, ' ');

		//popping animation for the bullet hitting something
		LinkedList<TileType> list = map[currentLevel].getListOfTileTypesAt(nextX, y);
		if(list.containsData(4, TileType::ENEMY, TileType::TERRAIN, TileType::NL_DOOR, TileType::PL_DOOR)) {
			mvwaddch(levelWindow, y, x, '*');
			wrefresh(levelWindow);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}else{
			mvwaddch(levelWindow, y, x, iter->data.getTileChar());
		}
		
		iter = iter->next;
	}
}

void Game::drawDoors(){
	int x,y;
	Object prevDoor = map[currentLevel].getPrevLevelDoor();
	Object nextDoor = map[currentLevel].getNextLevelDoor();
	prevDoor.getXY(x,y);

	mvwaddch(levelWindow,y,x, prevDoor.getTileChar());
	nextDoor.getXY(x,y);
	mvwaddch(levelWindow,y,x,nextDoor.getTileChar());
	wrefresh(levelWindow);
}

void Game::completeJump(Animation &proposedAnimation, Initiator &proposedInitiator){
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
}

//determines the Action to propose to Game::Logic() 
LinkedList<Action> Game::input(){
	nodelay(levelWindow, TRUE);
	noecho();

	Animation proposedAnimation = Animation::STILL;
	Initiator proposedInitiator = Initiator::LOGIC;
	char userKey = '_';

	LinkedList<TileType> listOfTileTypesAt; //this tells us all of the objects that are placed at x,y
	LinkedList<Action> proposedActions;		//this tells us everything that should happen given the userLog[] and the user-initiated actions
	
	//keeps the hero jumping till he moved JUMP_HEIGHT positions up in the Y-axis
	completeJump(proposedAnimation ,proposedInitiator);
	//has the hero fall each time a TileType::EMPTY is beneath him
	fallingMechanic(proposedAnimation, proposedInitiator);
	
	//this adds the logic-initiated actions (falling and completing the jump) to proposedActions
	int x = hero.getX(), y = hero.getY();
	nextXyFor(x,y,proposedAnimation);
	listOfTileTypesAt = map[currentLevel].getListOfTileTypesAt(x,y);
	
	while(!listOfTileTypesAt.isEmpty()){
		proposedActions.pushHead(new Node<Action>(getCorrespondingAction(proposedAnimation, proposedInitiator, listOfTileTypesAt.getHead()->data)));
		listOfTileTypesAt.popHead();
	}


	//key pressing detection mechanism
	//this adds the user-initiated actions to proposedActions
	x = hero.getX(), y = hero.getY();

	if((userKey = wgetch(levelWindow)) != ERR){
		proposedAnimation = getCorrespondingAnimation(userKey);
		proposedInitiator = Initiator::USER;
		
		nextXyFor(x,y, proposedAnimation);
		listOfTileTypesAt = map[currentLevel].getListOfTileTypesAt(x,y);
		
		while(!listOfTileTypesAt.isEmpty()){
			proposedActions.pushHead(new Node<Action>(getCorrespondingAction(proposedAnimation, proposedInitiator, listOfTileTypesAt.getHead()->data)));
			listOfTileTypesAt.popHead();
		}
	}

	if(proposedActions.isEmpty()){
		proposedActions.pushHead(new Node<Action>(getCorrespondingAction(proposedAnimation, proposedInitiator, TileType::EMPTY)));
	}

	return proposedActions;
}

Animation Game::getCorrespondingAnimation(char userKey){
	switch(userKey){
			case 'w':
			//maybe we can have the hero climb up a ladder
			return Animation::CLIMB_UP;
			break;

			case 'a':
			return Animation::LEFT;
			break;
			
			case 's':
			//climb down a ladder or no use
			return Animation::CLIMB_DOWN;
			break;
			
			case 'd':
			return Animation::RIGHT;
			break;
			
			case ' ':
			return Animation::JUMPING;
			break;

			case '0':{
				gameOver = true;
				//saveMapToFile();
				return Animation::STILL;
				break;
			}
			

			case 'p':
			//here code to stop all moving entities 
			//and to display some sort of PAUSE label somewhere
			return Animation::STILL;
			break;

			case 'f':
			return Animation::SHOOTING;
			break;

			default:
			return Animation::STILL;

		}
}

//returns an action to propose to Game::Logic()
Action Game::getCorrespondingAction(Animation animation, Initiator initiator, TileType ttAffected){
	int x = hero.getX(), y = hero.getY();
	nextXyFor(x,y,animation);
	return Action(animation, x, y, initiator, ttAffected);
}

//either accepts the action proposed by the user or forces an action by logic  
Action Game::getEngagedAction(Action proposedAction){
	/*int h, w;
	getmaxyx(levelWindow, h, w);*/
	
	//establishes the legality of the action
	switch(proposedAction.getAnimation()){

		case Animation::JUMPING:
		return jump(proposedAction);
		break;

		case Animation::LEFT:
		case Animation::RIGHT:
		return goLeftRight(proposedAction);
		break;

		case Animation::FALLING:
		return fall(proposedAction);
		break;
		
		case Animation::SHOOTING:
		return shoot(proposedAction);
		break;

		case Animation::STILL:{//cause actually hero is STILL and has an ENEMY below him when he's done with his jump
			return endOfFallingAction(proposedAction);
		}

		case Animation::CLIMB_UP:
		case Animation::CLIMB_DOWN:
		case Animation::PAUSE:
		case Animation::QUIT:
		default: // this if may be useless
		return proposedAction;
	}
}

//accepts or rejects left/right movement
Action Game::goLeftRight(Action proposedAction){
	int w = getmaxx(levelWindow);
	w--;
	
	//if hero will be in the map
	if(proposedAction.getX() >= 0 && proposedAction.getX() <= w){
		switch(proposedAction.getTtAffected()){
			case TileType::EMPTY:{
				hero.setXY(proposedAction.getX(), proposedAction.getY());
				return proposedAction;
				break;
			}

			case TileType::BONUS:{
				grabBonusAt(proposedAction.getX(), proposedAction.getY());
				hero.setXY(proposedAction.getX(), proposedAction.getY());
				return Action(proposedAction.getAnimation(), proposedAction.getX(), proposedAction.getY(), proposedAction.getInitiator(), TileType::BONUS);
				break;
			}
			
			case TileType::MALUS:{
				inflictMalusAt(proposedAction.getX(), proposedAction.getY());
				hero.setXY(proposedAction.getX(), proposedAction.getY());
				return Action(proposedAction.getAnimation(), proposedAction.getX(), proposedAction.getY(), proposedAction.getInitiator(), TileType::MALUS);
				break;
			}

			case TileType::XP:{
				gainXpAt(proposedAction.getX(), proposedAction.getY());
				hero.setXY(proposedAction.getX(), proposedAction.getY());
				proposedAction.setTtAffected(TileType::XP);
				return proposedAction;
				break;
			}
			case TileType::NL_DOOR:
			case TileType::PL_DOOR:{
				hero.setXY(proposedAction.getX(), proposedAction.getY());
				return proposedAction;
				break;
			}
			
			case TileType::ENEMY:
			case TileType::BULLET:
			case TileType::HERO:
			case TileType::TERRAIN:
			default:
			return Action(Animation::STILL, hero.getX(), hero.getY(), Initiator::LOGIC, TileType::HERO); 
		}
	}else return Action(Animation::STILL, hero.getX(), hero.getY(), Initiator::LOGIC, TileType::HERO);
	
	//probably need to generalize these functions to take the acting entity as a parameter
}

//accepts or rejects jumps
Action Game::jump(Action proposedAction){
	int h = getmaxy(levelWindow);
	if(proposedAction.getY()>0 && proposedAction.getY() <= h){
		if(map[currentLevel].countObjectsAt(proposedAction.getX(), proposedAction.getY()) == 0){
			if(hero.countMoves(Animation::JUMPING) < JUMP_HEIGHT && hero.countMoves(Animation::FALLING) == 0){
				hero.setXY(proposedAction.getX(), proposedAction.getY());
				return proposedAction;
			}
		}
	}
	return Action(Animation::STILL, hero.getX(), hero.getY(), Initiator::LOGIC, TileType::HERO);
}

//accepts or rejects falling
Action Game::fall(Action proposedAction){
	int h = getmaxy(levelWindow);
	if(proposedAction.getY() >= 0 && proposedAction.getY() < h){
		LinkedList<TileType> list = map[currentLevel].getListOfTileTypesAt(proposedAction.getX(), proposedAction.getY());
		if(list.isEmpty()){ //equivalent of TileType::EMPTY
			hero.setXY(proposedAction.getX(), proposedAction.getY());
			return proposedAction;
		}else{
			for(int i=0; i<list.getSize(); i++){
				switch(list[i]){
					case TileType::EMPTY:
					hero.setXY(proposedAction.getX(), proposedAction.getY());
					return proposedAction;
					break;

					case TileType::ENEMY:{ //damages the enemy
						Node<Entity>* enemy = map[currentLevel].getNodeAtIn(proposedAction.getX(), proposedAction.getY(), map[currentLevel].getEnemies());
						enemy->data.setHp(enemy->data.getHp() - hero.getDp());
						return Action(Animation::STILL, proposedAction.getX(), proposedAction.getY(), Initiator::LOGIC, TileType::ENEMY);
						break;
					}

					case TileType::PL_DOOR:{
						hero.setXY(proposedAction.getX(), proposedAction.getY());
						proposedAction.setTtAffected(TileType::PL_DOOR);
						return proposedAction;
						break;
					}
					case TileType::NL_DOOR:{
						hero.setXY(proposedAction.getX(), proposedAction.getY());
						proposedAction.setTtAffected(TileType::NL_DOOR);
						return proposedAction;
						break;
					}
			
					case TileType::TERRAIN:
					case TileType::BONUS: //gets the bonus
					case TileType::MALUS: //gets the malus	// prolly superflous				
					case TileType::HERO: 
					case TileType::SIZE: //ain't happening
					default:
					return Action(Animation::STILL, hero.getX(), hero.getY(), Initiator::LOGIC, TileType::HERO);
					break;
				}
			}
		}
		
	}
	return Action(Animation::STILL, hero.getX(), hero.getY(), Initiator::LOGIC, TileType::HERO);
}

//accept or rejects shooting
Action Game::shoot(Action proposedAction){
	if (hero.getWeapon()->getMagazineAmmo() > 0){
		if(proposedAction.getX() >= 0 && proposedAction.getX() <= getmaxx(levelWindow)){
			switch (proposedAction.getTtAffected()){
				case TileType::XP:
				case TileType::MALUS:
				case TileType::BULLET:
				case TileType::BONUS:
				case TileType::EMPTY:
				map[currentLevel].getBullets()->pushHead(new Node<Entity>(Entity(proposedAction.getX(), proposedAction.getY(), TileType::BULLET, 0, hero.getWeapon()->getDp(), hero.getDirection())));
				hero.getWeapon()->setMagazineAmmo(hero.getWeapon()->getMagazineAmmo() - 1);
				return proposedAction;
				break;

				case TileType::ENEMY:{
					//hurt the enemy
					hero.getWeapon()->setMagazineAmmo(hero.getWeapon()->getMagazineAmmo()-1);
					Node<Entity>* enemy = map[currentLevel].getNodeAtIn(proposedAction.getX(), proposedAction.getY(), map[currentLevel].getEnemies());
					enemy->data.setHp(enemy->data.getHp()-hero.getWeapon()->getDp());
					return proposedAction;
					break;
				}

				case TileType::TERRAIN:
				default:
				break;
			}
		}
	}
	return Action(Animation::STILL, hero.getX(), hero.getY(), Initiator::LOGIC, TileType::HERO);
}

void Game::moveBullets(){
	int w = getmaxx(levelWindow);

	//flying bullets mechanic
	if(!map[currentLevel].getBullets()->isEmpty()){
		int x, y;
		int nextX;
		Node<Entity>* iter = map[currentLevel].getBullets()->getHead();
		while(iter != NULL){
			iter->data.getXY(x,y);
			LinkedList<TileType> listAtCurrentXY = map[currentLevel].getListOfTileTypesAt(x,y);
			if(iter->data.getDirection() == Direction::RIGHT) nextX = x+1;
			else nextX = x-1;
			LinkedList<TileType> listAtNextXY = map[currentLevel].getListOfTileTypesAt(nextX, y);
			
			//this has a bullet and one of {terrain, enemy} intersect for one cycle before being popped so that draw can do it's job right
			while(!listAtCurrentXY.isEmpty()){
				switch(listAtCurrentXY.getHead()->data){
					//this will cause the node to be popped in the following if-else
					case TileType::ENEMY:
					case TileType::TERRAIN:
					case TileType::HERO:
					case TileType::NL_DOOR:
					case TileType::PL_DOOR:
					nextX = -2; 
					break;

					default:
					break;
				}
				listAtCurrentXY.popHead();
			}

			//if they're in 'legal'-ish positions
			if(nextX >= -1 && nextX<= w){
				if(listAtNextXY.isEmpty()){//i.e. TileType::EMTPY at (x,y)
					iter->data.setXY(nextX, y);
					iter = iter->next;
				}else{
					//what you do when a bullet intersects these TileType's 
					while(!listAtNextXY.isEmpty()){
						switch(listAtNextXY.getHead()->data){
							//just go through them
							case TileType::XP:
							case TileType::MALUS: //maybe we can destroy maluses by shooting them
							case TileType::BONUS: 
							case TileType::EMPTY: //ain't happening
							case TileType::BULLET:
							iter->data.setXY(nextX, y);
							break;

							//they intersect for a second but then are deleted by the above while(!listAtCurrentXY.isEmpty())
							case TileType::NL_DOOR:
							case TileType::PL_DOOR:
							case TileType::TERRAIN:
							iter->data.setXY(nextX, y);
							break;

							//harm the enemy and intersect for a moment (will be later deleted)
							case TileType::ENEMY:{
								Node<Entity>* enemy = map[currentLevel].getNodeAtIn(nextX, y, map[currentLevel].getEnemies());
								enemy->data.setHp(enemy->data.getHp()-hero.getWeapon()->getDp());
								iter->data.setXY(nextX, y);
								//hurt the enemy
								break;
							}
					
							case TileType::HERO: //this ain't happening (till i get the enemies to shoot)
							default:
							break;
						}
						iter = iter->next;
						listAtNextXY.popHead();
					}
				}
			}else{
				map[currentLevel].getBullets()->popNode(iter);
				iter = iter->next;
			}
			
		}
		
		//move the bullet in its current direction until it hits something
		//then decide what it does to each tileType

	}
}

void Game::nextXyFor(int &x, int &y, Animation animation){
	switch(animation){
		case Animation::JUMPING:
		y--;
		break;

		case Animation::FALLING:
		y++;
		break;

		case Animation::LEFT:
		x--;
		break;

		case Animation::RIGHT:
		x++;
		break;

		case Animation::SHOOTING:
		if(hero.getDirection() == Direction::LEFT) x--;
		else if(hero.getDirection() == Direction::RIGHT) x++;
		break;

		case Animation::CLIMB_DOWN:
		case Animation::CLIMB_UP:
		case Animation::PAUSE:
		case Animation::QUIT:
		case Animation::STILL:
		default:
		break;
	}
}

int Game::getCorrespondingDelay(Animation animation){
	//enum class Animation{CLIMB_UP, CLIMB_DOWN, LEFT, RIGHT, STILL, JUMPING, FALLING, QUIT, PAUSE, SHOOTING};
	int animationDelay[] = {0, 0, 12, 12, 0, 112, 112, 0, 0, 10};
	return animationDelay[(int)animation];
}

//i.e. what do you do when the block underneat you is ...?
Action Game::endOfFallingAction(Action proposedAction){
	//be mindful that this will be called when the Hero is still and has something beneath him
	LinkedList<TileType> list = map[currentLevel].getListOfTileTypesAt(proposedAction.getX(), proposedAction.getY()+1);
	if(list.isEmpty()){
		return proposedAction;
	}else{
		switch(list.getHead()->data){
			case TileType::ENEMY:{
				//hurt the enemy when falling over him
				fallingAttack(proposedAction.getX(), proposedAction.getY()+1);
				return Action(proposedAction.getAnimation(), proposedAction.getX(), proposedAction.getY(), proposedAction.getInitiator(), TileType::ENEMY);
				break;
			}
			case TileType::BONUS:{
				//grab the bonus when falling over it
				grabBonusAt(proposedAction.getX(), proposedAction.getY()+1);
				return Action(proposedAction.getAnimation(), proposedAction.getX(), proposedAction.getY()+1, proposedAction.getInitiator(), TileType::BONUS);
				break;
			}
			case TileType::MALUS:{
				//inflict pain when falling over a malus
				inflictMalusAt(proposedAction.getX(), proposedAction.getY()+1);
				return Action(proposedAction.getAnimation(), proposedAction.getX(), proposedAction.getY()+1, proposedAction.getInitiator(), TileType::MALUS);
				break;
			}
			case TileType::XP:{
				gainXpAt(proposedAction.getX(), proposedAction.getY()+1);
				proposedAction.setTtAffected(TileType::XP);
				proposedAction.setY(proposedAction.getY()+1);
				return proposedAction;
				break;
			}
			case TileType::NL_DOOR:
			case TileType::PL_DOOR:{
				proposedAction.setTtAffected(list.getHead()->data);
				proposedAction.setY(proposedAction.getY()+1);
				return proposedAction;
			}
			default:{
				return proposedAction;
				break;
			}
		}
	}	
}

//decides whether to damage an enemy sitting below the attacker or not
void Game::fallingAttack(int x, int y){
	Node<Entity>* enemy = map[currentLevel].getNodeAtIn(x,y, map[currentLevel].getEnemies());
	enemy->data.setHp(enemy->data.getHp()-hero.getDp());
}

void Game::fallingMechanic(Animation &proposedAnimation, Initiator &proposedInitiator){
	if(proposedAnimation == Animation::STILL && map[currentLevel].countObjectsAt(hero.getX(), hero.getY()+1) == 0){
		proposedAnimation = Animation::FALLING;
		proposedInitiator = Initiator::LOGIC;
	}
}

//gives the player the benefits of the bonus and deletes it
void Game::grabBonusAt(int x, int y){
	Node<Bonus>* bonus = map[currentLevel].getNodeAtIn(x,y, map[currentLevel].getBonuses());
		hero.setHp(hero.getHp() + bonus->data.getHp());
		bonus->data.setHp(0);
}

//inflicts the player the agony of the malus and deletes it
void Game::inflictMalusAt(int x, int y){
	Node<Malus>* malus = map[currentLevel].getNodeAtIn(x, y, map[currentLevel].getMaluses());
	hero.setHp(hero.getHp() - malus->data.getDp());
	malus->data.setHp(0);
}

void Game::gainXpAt(int x, int y){
	score++;
	Node<Object>* p = map[currentLevel].getNodeAtIn(x,y, map[currentLevel].getXps());
	map[currentLevel].getXps()->popNode(p);
}

void Game::mortician(TileType tt /*= TileType::ENEMY*/){
    switch(tt){
	    case TileType::ENEMY:{
	    	sweepItemsIn(map[currentLevel].getEnemies());
    		mortician(TileType::BONUS);
    		break;
    	}

		case TileType::BONUS:{
	    	sweepItemsIn(map[currentLevel].getBonuses());
	    	mortician(TileType::MALUS);
	    	break;
	    }

		case TileType::MALUS:{
		    sweepItemsIn(map[currentLevel].getMaluses());
			mortician(TileType::HERO);
	    	break;
	    }

		case TileType::HERO:{
			if(hero.getHp()<=0) {
            	gameOver = true;
        		return;
    		}
		}
		default:
		break;
		
    }
}

//as of now, moves one enemy back and forth on a 3 unit long line
void Game::moveEnemies(){
	//move
}

//poses constraints on what the user can do, mainly chosen from our own world
//and registers the last Action
void Game::logic(LinkedList<Action> proposedActions){
	moveBullets();
	moveEnemies();
	while(!proposedActions.isEmpty()){
		hero.registerMove(getEngagedAction(proposedActions.getHead()->data));
		proposedActions.popHead();
	}
	mortician(TileType::ENEMY);
}

void Game::mainLoop() {
	srand(time(NULL));

	initscr();
	start_color();
	init_color(COLOR_BLACK, 0,0,0);
	init_color(COLOR_YELLOW, 1000, 1000, 200);
	init_color(COLOR_RED, 1000, 1000, 0);
	init_color(COLOR_MAGENTA, 332, 210, 570);
	init_color(COLOR_BLUE, 30, 570, 820);
	init_color(COLOR_CYAN, 750, 750, 750);
	clear();
	refresh();

	int w, h;

	menu = Menu();
	menu.menuLoop();

	if(menu.getOption() == MenuOption::PLAY){
		getmaxyx(stdscr, h, w);
		int HUD_h = 1;
		h = h - HUD_h;
		levelWindow = newwin(h,w, HUD_h,0);
		
		init_pair(1, COLOR_WHITE, COLOR_BLACK);
		wbkgd(levelWindow, COLOR_PAIR(1));
		
		createMap();

		bool changeLevel = true;
		while(!gameOver){
			/*
			using namespace std::chrono;

			time_point<system_clock> frameStart;
			duration<double> frameTime; // frameTime indicates how much time the current frame has taken
			frameStart = system_clock::now();
			*/
			
			
			draw(changeLevel);
			logic(input());
			
			if(hero.getActionLog()[0].getTtAffected() == TileType::PL_DOOR ) {
				changeLevel = true;
				currentLevel--;
				int x,y;
				map[currentLevel].getNextLevelDoor().getXY(x,y);
				hero.setXY(x-1,y);
			}else if(hero.getActionLog()[0].getTtAffected() == TileType::NL_DOOR){
				changeLevel = true;
				addLevel();
			}
			else changeLevel = false;

			/*
			frameTime = system_clock::now() - frameStart;
	
			if(frameDelay > frameTime){
				std::this_thread::sleep_for(frameDelay - frameTime);
			}
			*/

			
		}
	}

	if(hero.getHp()<=0){
		//insert some "UR DEAD PAL" message here
	}
	endwin();
}

Menu Game::getMenu(){ return menu; }

void Game::saveMapToFile(){
	
	
	ofstream file;
	file.open("/home/user/projects/project-X-githubClone/projectX/output/map.txt",  ofstream::out);

	for(int i=0; i<map.getSize(); i++){
		for(int y=0; y<=map[i].getVertBound(); y++){
			for(int x=0; x<=map[i].getHorBound(); x++){
				LinkedList<TileType> list = map[i].getListOfTileTypesAt(x,y);
				if(list.isEmpty()) file.put(' ');
				else file.put(getTTchar(list.getHead()->data));
			}
			file.put('\n');
		}
		file.put('\n');file.put('!');file.put('\n');
	}
	file.close();
}

char Game::getTTchar(TileType tt){
	char tileChar[]{ ' ', '#', 'H', 'E', 'B', 'M', 'o', '&', '&','$'};
    return tileChar[(int)tt];
}