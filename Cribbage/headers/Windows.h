#ifndef WINDOWS_H
#define WINDOWS_H

#include <string>
#include <vector>
#include <map>
#include <pdcurses/curses.h>

WINDOW* CreateNewWin(std::vector<int>);
WINDOW* CreateNewWinBorder(std::vector<int>);

void DestroyWin(WINDOW*);

void MVPrintWSA(int, int, std::vector<std::string>);

void MVWPrintWSA(WINDOW*, int, int, std::vector<std::string>, std::vector<int>);

void MVWPrintWColoured(WINDOW*, int, int, std::map<int, std::vector < std::string>>);

#endif