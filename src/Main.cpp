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
        data.print_title();
        if (data._inMenu) {
            data.print_menu();
            data.get_input_menu();
        } else {
            switch (data._set) {
                case 0: data.launch_ct(); break;
            }
        }
        refresh();
    }
    return 0;
}
