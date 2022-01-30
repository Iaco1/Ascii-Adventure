#include "Menu.hpp"
#include <iostream>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

Menu::Menu() {

}

//prints the title
WINDOW* Menu::printStartScreen() {
    clear();
    refresh();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    int title_h = 14;
    int title_w = 52;
    int h, w;
    getmaxyx(stdscr, h, w);
    WINDOW* title = newwin(title_h, title_w, h / 2 - title_h / 2 - 3, w / 2 - title_w / 2);
    WINDOW* belowTitle = newwin(3, 30 + 2, h - 4, w / 2 - 16); // used to write the press space to play

    curs_set(0);
    wattron(title, COLOR_PAIR(1));
    mvwprintw(title, 0, 0, "                   _     ______ _____ _____ ");
    wrefresh(title);
    refresh();
    usleep(200000);
    mvwprintw(title, 1, 0, "           /\\     | |   / _____|_____|_____)");
    wrefresh(title);
    refresh();
    usleep(200000);
    mvwprintw(title, 2, 0, "          /  \\     \\ \\ | /        _     _   ");
    wrefresh(title);
    refresh();
    usleep(200000);
    mvwprintw(title, 3, 0, "         / /\\ \\     \\ \\| |       | |   | |  ");
    wrefresh(title);
    refresh();
    usleep(200000);
    mvwprintw(title, 4, 0, "        | |__| |_____) ) \\_____ _| |_ _| |_ ");
    wrefresh(title);
    refresh();
    usleep(200000);
    mvwprintw(title, 5, 0, "        |______(______/ \\______|_____|_____)");
    wrefresh(title);
    refresh();
    usleep(200000);
    mvwprintw(title, 6, 0, "            _                                       ");
    wrefresh(title);
    refresh();
    usleep(200000);
    mvwprintw(title, 7, 0, "   /\\      | |                 _                    ");
    wrefresh(title);
    refresh();
    usleep(200000);
    mvwprintw(title, 8, 0, "  /  \\   _ | |_   _ ____ ____ | |_ _   _  ____ ____ ");
    wrefresh(title);
    refresh();
    usleep(200000);
    mvwprintw(title, 9, 0, " / /\\ \\ / || | | | / _  )  _ \\|  _) | | |/ ___) _  )");
    wrefresh(title);
    refresh();
    usleep(200000);
    mvwprintw(title, 10, 0, "| |__| ( (_| |\\ V ( (/ /| | | | |_| |_| | |  ( (/ / ");
    wrefresh(title);
    refresh();
    usleep(200000);
    mvwprintw(title, 11, 0, "|______|\\____| \\_/ \\____)_| |_|\\___)____|_|   \\____)");
    wrefresh(title);
    refresh();
    sleep(1);
    wattroff(title, COLOR_PAIR(1));
    mvwprintw(title, 13, 0, "     [ by Davide Iacomino & Leonardo Mancini ]");
    wrefresh(title);
    refresh();

    sleep(1);

    w = getmaxx(belowTitle);
    wattron(belowTitle, COLOR_PAIR(2));
    mvwprintw(belowTitle, 1, 1, "Press SPACE to enter the menu");
    wrefresh(belowTitle);
    wattroff(belowTitle, COLOR_PAIR(2));

    return belowTitle;
}

//prints the main menu
void Menu::printMenu() {
    clear();
    int title_h = 4;
    int title_w = 15;
    int h, w;
    getmaxyx(stdscr, h, w);
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    mvprintw(h / 2 - title_h / 2 - 1, w / 2 - title_w / 2, "ASCII Adventure");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    mvprintw(h / 2 - title_h / 2 + 1, w / 2 - title_w / 2, "   1 - PLAY");
    mvprintw(h / 2 - title_h / 2 + 2, w / 2 - title_w / 2, "   0 - QUIT");
    attroff(COLOR_PAIR(2));
    refresh();
}

//prints option 0 of the main menu
void Menu::printEndScreen() {
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    mvprintw(getmaxy(stdscr) / 2 - 1, getmaxx(stdscr) / 2 - 7, "See you soon!");
    attroff(COLOR_PAIR(1));
    refresh();
    option = MenuOption::EXIT;
    sleep(2);
    system("reset");
}

//prints a start game message
void Menu::initGame() {
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(2));
    mvprintw(getmaxy(stdscr) / 2 - 1, getmaxx(stdscr) / 2 - 8, "The game starts");
    refresh();
    sleep(1);
    mvprintw(getmaxy(stdscr) / 2, getmaxx(stdscr) / 2 - 18, "We wish for you to have a good time");
    attroff(COLOR_PAIR(2));
    refresh();
    sleep(1);
    option = MenuOption::PLAY;
}

//menu loop logic
void Menu::menuLoop() {
    char choice;
    WINDOW* bt = printStartScreen();
    do {

        choice = wgetch(bt);
    } while (choice != ' ');
    choice = '_';

    while (choice != '0' && choice != '1') {
        printMenu();
        choice = getch();
    }

    clear();
    switch (choice) {
    case '0':
        printEndScreen();
        break;

    case '1':
        initGame();
        printHelpScreen();
        break;

    default:
        cout << "you're not supposed to be here";

    }
    sleep(3);
}

//prints commands and a description of the game elements
void Menu::printHelpScreen() {
    clear();
    refresh();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_GREEN, COLOR_BLACK);
    init_pair(8, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(9, COLOR_RED, COLOR_BLACK);

    attron(COLOR_PAIR(1));
    mvprintw(getmaxy(stdscr) / 8, getmaxx(stdscr) / 8, "HELP LOG");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(6));
    mvaddch(getmaxy(stdscr) / 8 + 3, getmaxx(stdscr) / 8, 'H');
    attroff(COLOR_PAIR(6));
    mvprintw(getmaxy(stdscr) / 8 + 3, getmaxx(stdscr) / 8 + 10, "this is you, the hero");

    attron(COLOR_PAIR(9));
    mvprintw(getmaxy(stdscr) / 8 + 5, getmaxx(stdscr) / 8, "S B");
    attroff(COLOR_PAIR(9));
    mvprintw(getmaxy(stdscr) / 8 + 5, getmaxx(stdscr) / 8 + 10, "enemies");


    attron(COLOR_PAIR(7));
    mvprintw(getmaxy(stdscr) / 8 + 7, getmaxx(stdscr) / 8, "+ a A K");
    attroff(COLOR_PAIR(7));
    mvprintw(getmaxy(stdscr) / 8 + 7, getmaxx(stdscr) / 8 + 10, "bonuses");

    attron(COLOR_PAIR(8));
    mvprintw(getmaxy(stdscr) / 8 + 9, getmaxx(stdscr) / 8, "| m W");
    attroff(COLOR_PAIR(8));
    mvprintw(getmaxy(stdscr) / 8 + 9, getmaxx(stdscr) / 8 + 10, "traps");

    mvprintw(getmaxy(stdscr) / 8 + 11, getmaxx(stdscr) / 8, "$");
    mvprintw(getmaxy(stdscr) / 8 + 11, getmaxx(stdscr) / 8 + 10, "XP points");

    mvprintw(getmaxy(stdscr) / 8 + 13, getmaxx(stdscr) / 8, "&");
    mvprintw(getmaxy(stdscr) / 8 + 13, getmaxx(stdscr) / 8 + 10, "door to next level");

    attron(COLOR_PAIR(6));
    mvprintw(getmaxy(stdscr) / 8 + 16, getmaxx(stdscr) / 2 - 12, "Press SPACE to continue");
    attroff(COLOR_PAIR(6));

    attron(COLOR_PAIR(1));
    mvprintw(getmaxy(stdscr) / 8, getmaxx(stdscr) * 3 / 4 - 14, "COMMANDS                    ");
    attroff(COLOR_PAIR(1));
    mvprintw(getmaxy(stdscr) / 8 + 3, getmaxx(stdscr) * 3 / 4 - 14, "left-right movement:    A, D");
    mvprintw(getmaxy(stdscr) / 8 + 5, getmaxx(stdscr) * 3 / 4 - 14, "jump:                  SPACE");
    mvprintw(getmaxy(stdscr) / 8 + 7, getmaxx(stdscr) * 3 / 4 - 14, "shoot:                     F");
    mvprintw(getmaxy(stdscr) / 8 + 9, getmaxx(stdscr) * 3 / 4 - 14, "return to main screen:     0");
    refresh();
    while (getch() != ' ');
    clear();
}

MenuOption Menu::getOption() { return option; }

