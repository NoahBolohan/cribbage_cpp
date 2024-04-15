#ifndef WINDOWS_H
#define WINDOWS_H

#include <string>
#include <vector>
#include <pdcurses/curses.h>

WINDOW* create_newwin(std::vector<int>);
WINDOW* create_newwin_border(std::vector<int>);

void destroy_win(WINDOW*);

void mvprintw_sa(int, int, std::vector<std::string>);

void mvwprintw_sa(WINDOW*, int, int, std::vector<std::string>);

#endif