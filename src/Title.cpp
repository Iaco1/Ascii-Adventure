#include "Title.hpp"

Title::Title(){
        NWx = 1;
        NWy = 1;
        titleString[0] = "    ____ ___   ____  ___    ____  ";
        titleString[1] = "   / __ )__ \\ / __ \\/   |  / __ \\ ";
        titleString[2] = "  / __  |_/ // / / / /| | / /_/ / ";
        titleString[3] = " / /_/ / __// /_/ / ___ |/ ____/  ";
        titleString[4] = "/_____/____/_____/_/  |_/_/       ";
        for(width = 0; titleString[1][width]!='\0'; width++);
        height = 5;
    }
Title::Title(int windowCenterX, int windowCenterY){
        titleString[0] = "    ____ ___   ____  ___    ____  ";
        titleString[1] = "   / __ )__ \\ / __ \\/   |  / __ \\ ";
        titleString[2] = "  / __  |_/ // / / / /| | / /_/ / ";
        titleString[3] = " / /_/ / __// /_/ / ___ |/ ____/  ";
        titleString[4] = "/_____/____/_____/_/  |_/_/       ";
        for(width = 0; titleString[1][width]!='\0'; width++);
        height = 5;
        //setting the NW coordinates so that the center of the title area sits 
        //in the center of the window's area 
        NWx = windowCenterX - width/2;
        NWy = windowCenterY - height/2;
    }
int Title::getNWx(){ return NWx; }
int Title::getNWy(){ return NWy; }
int Title::getHeight(){ return height; }
int Title::getWidth(){ return width; }
const char* Title::getTitleString(int i){ return titleString[i]; }
