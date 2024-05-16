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
    if (_nbAttemptsCT)
        mvprintw(_historyY - 1, (_screenX / 2) - 20, "|    Type    |  Puissance  |  Précision  |");
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
        mvprintw(i, 0, "               ");
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
    int i = 0;
    bool isValid = false;

    for(; i < CT_COUNT - 1 && !isValid; i++) {
        if (transformStr(CtNames[i]) == transformStr(guess)) {
            isValid = true;
            // VICTORY CONDITION
            if (i == _dailyCT) {
                save_score_ct();
                exit(0);
                // return;
            }
        }
    }
    if (isValid)
        print_clues_ct(i);
    else if (!guess.empty()) {
        bool same;
        for (int j = 0; j < CT_COUNT - 1; j++) {
            same = true;
            for (i = 0; guess[i]; i++) {
                if (transformStr(CtNames[j])[i] != transformStr(guess)[i]) {
                    same = false;
                    break;
                }
            }
            if (same) {
                print_clues_ct(j);
                break;
            }
        }
    }
}

void Interface::print_clues_ct(const int i)
{
    bool isCopy = false;
    for (int j = 0; j < _nbAttemptsCT && !isCopy; j++) {
        if (_listAttempsCT[j] == i) {
            isCopy = true;
            break;
        }
    }
    if (!isCopy) {
        _nbAttemptsCT++;
        _listAttempsCT[_nbAttemptsCT - 1] = i;
        move(1, 0);//debug
        clrtoeol();//debug
        mvprintw(1, 1, ("Nuh uh " + std::to_string(_nbAttemptsCT)).c_str());//debug
        int cmp = 1;
        for (int j = _nbAttemptsCT - 1; j >= 0; j--) {
            int y = _historyY + cmp;
            cmp++;
            int x = (_screenX / 2) - 20;
            move(y, 0);
            clrtoeol();
            mvprintw(y, x - CtNames[_listAttempsCT[j]].size() - 2, "%s  | ", CtNames[_listAttempsCT[j]].c_str());

            // types
            if (CtTypes[_listAttempsCT[j]] != CtTypes[_dailyCT])
                attron(COLOR_PAIR(3));
            else
                attron(COLOR_PAIR(4));
            mvprintw(y, x + 2, CtTypes[_listAttempsCT[j]].c_str());

            attron(COLOR_PAIR(1));
            mvprintw(y, x + 13, "| ");


            // powers
            if (CtPower[_listAttempsCT[j]] != CtPower[_dailyCT]) {
                attron(COLOR_PAIR(3));
                if (CtPower[_listAttempsCT[j]] < CtPower[_dailyCT])
                    mvprintw(y, x + 13 + 12, "^");
                else
                    mvprintw(y, x + 13 + 12, "v");

            } else {
                attron(COLOR_PAIR(4));
            }
            mvprintw(y, x + 15, std::to_string(CtPower[_listAttempsCT[j]]).c_str());

            attron(COLOR_PAIR(1));
            mvprintw(y, x + 13 + 14, "| ");


            // accuracy
            if (CtAccuracy[_listAttempsCT[j]] != CtAccuracy[_dailyCT]) {
                attron(COLOR_PAIR(3));
                if (CtAccuracy[_listAttempsCT[j]] < CtAccuracy[_dailyCT])
                    mvprintw(y, x + 13 + 14 + 12, "^");
                else
                    mvprintw(y, x + 13 + 14 + 12, "v");
            } else {
                attron(COLOR_PAIR(4));
            }
            mvprintw(y, x + 13 + 16, std::to_string(CtAccuracy[_listAttempsCT[j]]).c_str());
            
            attron(COLOR_PAIR(1));
            mvprintw(y, x + 13 + 14 + 14, "|");
        }
    }
}

void Interface::save_score_ct()
{
    std::ofstream file("db/ctSave.xml", std::ios::trunc);

    if (!file.is_open())
        std::cerr << "File error: open." << std::endl;

    file << "<" << "document" << ">" << std::endl;
    file << "\t" << "<header title=\"CT Save\">" << std::endl;
    file << "\t\t" << "<date>" << "EXAMPLE 2024-01-01 EXAMPLE" << "</date>" << std::endl;
    file << "\t" << "</header>" << std::endl;

    file << "\t" << "<body>" << std::endl;
    file << "\t\t" << "<paragraph>" << _nbAttemptsCT + 1 << "</paragraph>" << std::endl;
    file << "\t\t" << "<list>" << std::endl;
        // loop and print each attemps informations (in reverse order)
    file << "\t\t" << "</list>" << std::endl;
    file << "\t" << "</body>" << std::endl;
    file << "</" << "document" << ">" << std::endl;

    file.close();
}