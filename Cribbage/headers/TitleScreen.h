#ifndef TITLE_SCREEN_HEADER
#define TITLE_SCREEN_HEADER

#include <pdcurses/curses.h>

void StartGame();
void DisplayTitleScreen();
int DisplayOptionsScreen(int);
int DisplayNPlayerMenu(char, int, int);
void ExitGame();

#endif