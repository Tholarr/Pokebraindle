/*
** PERSONAL PROJECT, 2024
** Pokebraindle
** File description:
** Interface
*/
#include "include/Interface.hpp"

Interface::Interface() 
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    getmaxyx(stdscr, _screenY, _screenX);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);

    _cursor = 0;
    _inMenu = true;
    _set = -1;

    _dailyCT = 5;
    _nbAttemptsCT = 0;
    _historyY = 19;
}

Interface::~Interface()
{
    clear();
    endwin();
}

void Interface::print_title()
{
    const std::vector<std::string> title_lines = {
        "   ___      _        _               _           _ _      ",
        "  / _ \\___ | | _____| |__  _ __ __ _(_)_ __   __| | | ___ ",
        " / /_)/ _ \\| |/ / _ \\ '_ \\| '__/ _` | | '_ \\ / _` | |/ _ \\",
        "/ ___/ (_) |   <  __/ |_) | | | (_| | | | | | (_| | |  __/",
        "\\/    \\___/|_|\\_\\___|_.__/|_|  \\__,_|_|_| |_|\\__,_|_|\\___|"
    };
    getmaxyx(stdscr, _screenY, _screenX);
    int start_x = (_screenX - title_lines[0].length()) / 2;
    int start_y = 3;

    attron(COLOR_PAIR(1));
    for (size_t i = 0; i < title_lines.size(); ++i) {
        mvprintw(start_y + i, start_x, title_lines[i].c_str());
    }
}

void Interface::print_menu()
{
    const std::vector<std::string> title_lines = {
        "CT",
        "Object",
        "Attack",
    };
    getmaxyx(stdscr, _screenY, _screenX);
    int start_y = _screenY / 2 - title_lines.size() / 2;

    for (size_t i = 0; i < title_lines.size(); ++i) {
        int start_x = (_screenX - title_lines[i].length()) / 2;
        if (_cursor == i)
            attron(COLOR_PAIR(2));
        else
            attron(COLOR_PAIR(1));
        mvprintw(start_y + i, start_x, title_lines[i].c_str());
    }
}

void Interface::get_input_menu()
{
    int input = getch();

    switch(input) {
        case '\n': update_cursor(0); break; // "enter" key
        case KEY_UP: update_cursor(-1); break;
        case KEY_DOWN: update_cursor(1); break;
    }
}

void Interface::update_cursor(int code)
{
    void (Interface::*fonctions[])() = {
        &Interface::launch_ct,
        &Interface::launch_obj,
        &Interface::launch_att
    };

    if (code == 0 && _cursor == 0) {
        _inMenu = false;
        _set = _cursor;
        clear();
        // (this->*fonctions[_cursor])();
    }
    if (code == -1 && _cursor > 0)
        _cursor--;
    if (code == 1 && _cursor < 2)
        _cursor++;
}
