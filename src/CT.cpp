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
    mvprintw(14, (_screenX / 2) - 7, "_______________");
    mvprintw(16, (_screenX / 2) - 7, "_______________");
    mvprintw(15, (_screenX / 2) - 9, "|");
    mvprintw(15, (_screenX / 2) + 9, "|");
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
        if (str.size() < 13)
            str += input;
    } else {
        if (!str.empty()) {
            str.pop_back();
            move(15, 0);
            clrtoeol();
        }
    }
    mvprintw(15, (_screenX / 2) - 6, str.c_str());
    print_suggestions_ct(transformStr(str));
    refresh();
}

std::string Interface::transformStr(const std::string& str)
{
    std::string lowStr;
    std::locale loc;
    
    for (char ch : str) {
        if (std::isupper(ch, loc))
            ch = std::tolower(ch, loc);
        lowStr += ch;
    }

    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    std::u32string u32str = converter.from_bytes(lowStr);
    std::wstring wstr(u32str.begin(), u32str.end());
    std::wstring result;

    for (char32_t c : wstr) {
        switch (c) {
            case U'à': case U'â': case U'ä': result += L'a'; break;
            case U'é': case U'è': case U'ê': case U'ë': result += L'e'; break;
            case U'î': case U'ï': result += L'i'; break;
            case U'ô': case U'ö': result += L'o'; break;
            case U'ù': case U'û': case U'ü': result += L'u'; break;
            case U'ç': result += L'c'; break;
            default: result += c;
        }
    }
    return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(result);
}

void Interface::print_suggestions_ct(const std::string guess)
{
    size_t start_y = 10;
    bool same;

    for (int i = start_y; i < CT_COUNT; i++)
        mvprintw(i, 0, "                    ");
    if (!guess.empty()) {
        for (const auto& ctName : CtNames) {
            same = true;
            for (size_t i = 0; guess[i]; i++) {
                if (transformStr(ctName)[i] != guess[i]) {
                    same = false;
                    break;
                }
            }
            if (same) {
                mvprintw(start_y, 1, ctName.c_str());
                start_y++;
            }
        }
    }
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
