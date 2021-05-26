#include "Menu.hpp"

//size is the no. elements in TileType
enum class TileType{ EMPTY, TERRAIN, PLATFORM, HERO, ENEMY, BONUS, MALUS, SIZE };

class Level{
    TileType Board[WINDOW_HEIGHT][WINDOW_WIDTH];
};