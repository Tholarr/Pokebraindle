#include "include/Interface.hpp"

Interface::Interface() 
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    getmaxyx(stdscr, _screenY, _screenX);
    _cursor = 0;
    _inMenu = true;
}

Interface::~Interface()
{
    clear();
    endwin();
}

void Interface::print_title(int y)
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
    int start_y = _screenY / 2 - title_lines.size() / 2 - (title_lines.size() + 2);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
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

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    for (size_t i = 0; i < title_lines.size(); ++i) {
        int start_x = (_screenX - title_lines[i].length()) / 2;
        if (_cursor == i)
            attron(COLOR_PAIR(2));
        else
            attron(COLOR_PAIR(1));
        mvprintw(start_y + i, start_x, title_lines[i].c_str());
    }
}

void Interface::get_input()
{
    int input = getch();

    if (_inMenu) {
        switch(input) {
            case KEY_UP:
                update_cursor(-1);
                break;
            case KEY_DOWN:
                update_cursor(1);
                break;
        }
    }
}

void Interface::update_cursor(int direction)
{
    if (direction == -1 && _cursor > 0)
        _cursor--;
    if (direction == 1 && _cursor < 2)
        _cursor++;
}
