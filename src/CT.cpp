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
    const std::string title = "Devine la CT d'aujourd'hui!";
    getmaxyx(stdscr, _screenY, _screenX);

    attron(COLOR_PAIR(1));
    mvprintw(10, (_screenX - title.length()) / 2, title.c_str());

}
