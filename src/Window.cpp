#include "Window.hpp"


Window::Window(){
        width = 128;
        height = 32;
        centerX = width/2;
        centerY = height/2;
}
Window::Window(int w, int h){
        if(w>0 && h>0){
            width = w;
            height = h;
            centerX = width/2;
            centerY = height/2;
        }else{
            Window();
        }
        
    }

int Window::getCenterX(){ return centerX; }
int Window::getCenterY(){ return centerY; }
int Window::getWidth(){ return width; }
int Window::getHeight(){ return height; }