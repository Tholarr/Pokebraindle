/*
** PERSONAL PROJECT, 2024
** Pokebraindle
** File description:
** CT
*/
#include "include/Interface.hpp"

void Interface::launch_obj() {}
void Interface::launch_att() {}

void Interface::launch_ct()
{
    getmaxyx(stdscr, _screenY, _screenX);
    attron(COLOR_PAIR(1));
    mvprintw(10, (_screenX / 2) - 14, "Devine la CT d'aujourd'hui!");
    mvprintw(14, (_screenX / 2) - 7, "_____________");
    mvprintw(16, (_screenX / 2) - 7, "_____________");
    mvprintw(15, (_screenX / 2) - 9, "|");
    mvprintw(15, (_screenX / 2) + 7, "|");
    get_input_ct();
}

void Interface::get_input_ct()
{
    int input = getch();
    static std::string str = "";
    
    if (input == '\n') {
        get_answer_ct(str);
        str.clear();
        move(15, 0);
        clrtoeol();
    } else if (input != KEY_BACKSPACE) {
        if (str.size() < 11)
            str += input;
    } else {
        if (!str.empty()) {
            str.pop_back();
            move(15, 0);
            clrtoeol();
        }
    }
    mvprintw(15, (_screenX - str.length()) / 2, str.c_str());
    refresh();
}

void Interface::get_answer_ct(const std::string guess)
{
    for(size_t i = 0; i < CT_COUNT; i++) {
        if (CtNames[i] == guess) {
            if (i == _dailyCT)
                mvprintw(0, 0, "congrats!");
        }
    }
}
