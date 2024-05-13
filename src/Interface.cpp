#include "include/Interface.hpp"

Interface::Interface() 
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, _screenY, _screenX);
}

Interface::~Interface()
{
    clear();
    endwin();
}

void Interface::print_title(int y)
{
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(1));

    std::string message1 = "   ___      _        _               _           _ _      ";
    std::string message2 = "  / _ \\___ | | _____| |__  _ __ __ _(_)_ __   __| | | ___ ";
    std::string message3 = " / /_)/ _ \\| |/ / _ \\ '_ \\| '__/ _` | | '_ \\ / _` | |/ _ \\";
    std::string message4 = "/ ___/ (_) |   <  __/ |_) | | | (_| | | | | | (_| | |  __/";
    std::string message5 = "\\/    \\___/|_|\\_\\___|_.__/|_|  \\__,_|_|_| |_|\\__,_|_|\\___|";
    int message_length = message1.length();
    int start_x = (_screenX - message_length) / 2;
    int start_y = _screenY / 2 + y;
    mvprintw(start_y, start_x, message1.c_str());
    mvprintw(start_y+1, start_x, message2.c_str());
    mvprintw(start_y+2, start_x, message3.c_str());
    mvprintw(start_y+3, start_x, message4.c_str());
    mvprintw(start_y+4, start_x, message5.c_str());
}