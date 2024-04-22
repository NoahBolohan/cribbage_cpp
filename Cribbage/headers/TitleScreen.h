#ifndef TITLE_SCREEN_HEADER
#define TITLE_SCREEN_HEADER

#include <tuple>
#include <map>
#include <string>
#include <pdcurses/curses.h>

// Screen diaplays
void StartGame(int, std::map<int, std::string>);
void DisplayTitleScreen();
std::tuple<int, std::map<int, std::string>> DisplayOptionsScreen(int, std::map<int, std::string>);

// Option menu displays
int DisplayNPlayerMenu(char, int, int);
std::map<int, std::string> DisplayPlayerColoursMenu(char, std::map<int, std::string>, int);

// Exit game
void ExitGame();

#endif