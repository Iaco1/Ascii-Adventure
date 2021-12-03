#include "Object.hpp"
#include <cstdlib>
#include <cstdio>
#include <cstring>

Object::Object(){
        x=0;
        y=0;
        tileType = TileType::EMPTY;
    }

Object::Object(int x, int y, TileType tileType){
        if(x>=0 && y>=0){
            this->x = x;
            this->y = y;
            this->tileType = tileType;
        }else{
            Object();
        }
    }

Object::Object(bool random){
    if(random==true){
			x = rand()%100;
			y = rand()%20;
			tileType = static_cast<TileType>(rand()%(static_cast<int>(TileType::SIZE)));
	}else Object();
}

void Object::toString(char str[24]){
	const char* tileTypeStr[] = {"Empty", "Terrain", "Hero", "Enemy", "Bonus", "Malus"};
    sprintf(str, "((%d,%d),%s)", x, y, tileTypeStr[(int)tileType]);
}

void Object::getXY(int &x, int &y){
    x = this->x;
    y = this->y;
}

char Object::getTileChar(){
    char tileChar[]{ ' ', '#', 'H', 'E', 'B', 'M' };
    return tileChar[(int)tileType];
}

void Object::setXY(int x, int y){
    if(x>=0 && y>=0){
        this->x = x;
        this->y = y;
    }
}

TileType Object::getTileType(){ return tileType; }

int Object::getX(){ return x; }
int Object::getY(){ return y; }