#include "Object.hpp"

Object::Object(){
        x=0;
        y=0;
        tiletype = TileType::EMPTY;
    }

Object::Object(int x, int y, TileType tiletype){
        if(x>0 && y>0){
            this->x = x;
            this->y = y;
            this->tiletype = tiletype;
        }else{
            Object();
        }
    }