#ifndef TITLE_SCREEN_HEADER
#define TITLE_SCREEN_HEADER

#include <tuple>
#include <map>
#include <string>
#include <pdcurses/curses.h>

// Screen diaplays
void StartGame(int, std::map<int, int>);
void DisplayTitleScreen(int);
std::tuple<int, std::map<int, int>> DisplayOptionsScreen(int, std::map<int, int>);
void DisplayOptionsScreenOptions(int);

// Option menu displays
int DisplayNPlayerMenu(char, int);
std::map<int, int> DisplayPlayerColoursMenu(char, std::map<int, int>);

// Exit game
void ExitGame();

#endif