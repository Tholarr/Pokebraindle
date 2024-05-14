/*
** PERSONNAL PROJECT, 2024
** Pokebraindle
** File description:
** Interface
*/

#ifndef CT_HPP_
    #define CT_HPP_
#include <ncurses.h>
#include <string>
#include <iostream>
#include <vector>
#include "Ct.hpp"

class Interface {
    public:
        Interface();
        ~Interface();
        void print_title();
        void print_menu();
        void get_input();
        void update_cursor(int code);
        void launch_ct();
        void launch_obj();
        void launch_att();

        bool _inMenu;
        int _set;

    protected:
        int _cursor;
        int _screenY;
        int _screenX;
};


#endif /* !CT_HPP_ */
