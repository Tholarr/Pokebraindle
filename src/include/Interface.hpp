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
#include "Ct.hpp"

class Interface {
    public:
        Interface(/* args */);
        ~Interface();
        void print_title(int y);

    protected:
        int _screenY;
        int _screenX;
};


#endif /* !CT_HPP_ */
