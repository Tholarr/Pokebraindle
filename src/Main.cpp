/*
** PERSONAL PROJECT, 2024
** Pokebraindle
** File description:
** Main
*/
#include "include/Interface.hpp"

int main()
{
    Interface data;

    while(1) {
        data.print_title(-4);
        if (data._inMenu)
            data.print_menu();
        refresh();
        data.get_input();
    }
    return 0;
}
