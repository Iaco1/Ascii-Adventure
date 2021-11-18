#include "Window.hpp"
#include <ncurses.h>


Window::Window(){
        width = 128;
        height = 32;
        centerX = width/2;
        centerY = height/2;
}
Window::Window(int w, int h){
    w-=2;h-=2; //adjusts the size of the screen to include the borders being drawn
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
void Window::printFrame() {
    const char frameChar1 = '-', frameChar2 = ':';
    for(int i=0; i <= width; i++) {
        mvaddch(0,i,frameChar1);
        mvaddch(height,i,frameChar1);
        refresh();
    }
    for(int i=1; i<=height-1; i++){
        mvaddch(i, 0, frameChar2);
        mvaddch(i, width, frameChar2);
        refresh();
    }
    move(height, width);
    refresh();
}