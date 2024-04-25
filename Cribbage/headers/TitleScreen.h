#ifndef TITLE_SCREEN_HEADER
#define TITLE_SCREEN_HEADER

#include <tuple>
#include <map>
#include <string>
#include <pdcurses/curses.h>
#include "Windows.h"

// Screen diaplays
void StartGame(int, std::map<int, int>);
void DisplayTitleScreen(WINDOW*, int);
std::tuple<int, std::map<int, int>> DisplayOptionsScreen(WINDOW*, int, std::map<int, int>);
void DisplayOptionsScreenOptions(WINDOW*, int);

// Option menu displays
int DisplayNPlayerMenu(WINDOW*, char, int);
std::map<int, int> DisplayPlayerColoursMenu(WINDOW*, char, int, std::map<int, int>);

// Exit game
void ExitGame();

#endif