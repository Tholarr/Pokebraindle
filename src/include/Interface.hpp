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
#include <locale>
#include <codecvt>
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
        void print_suggestions_ct(const std::string guess);
        std::string transformStr(const std::string& str);
        void get_answer_ct(const std::string guess);
        void print_clues_ct(const int i);

        void launch_obj();
        void launch_att();

        bool _inMenu;
        int _set;
        int _dailyCT;
        int _nbAttemptsCT;
        std::array<int, CT_COUNT> _listAttempsCT;

    protected:
        int _cursor;
        int _screenY;
        int _screenX;
        int _historyY;

};


#endif /* !INTERFACE_HPP_ */
