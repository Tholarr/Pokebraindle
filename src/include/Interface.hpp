/*
** PERSONNAL PROJECT, 2024
** Pokebraindle
** File description:
** Interface
*/

#ifndef INTERFACE_HPP_
    #define INTERFACE_HPP_
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
        void get_input_menu();
        void update_cursor(int code);

        void launch_ct();
        void get_input_ct();
        void get_answer_ct(const std::string);

        void launch_obj();
        void launch_att();

        bool _inMenu;
        int _set;
        int _dailyCT;

    protected:
        int _cursor;
        int _screenY;
        int _screenX;

};


#endif /* !INTERFACE_HPP_ */
