
//
//int main() {
//
//	initscr();
//	int number_of_players = 3;
//
//	Cribbage cribbage(number_of_players);
//	cribbage.StartGame();
//
//	getch();
//
//	return 0;
//}

#include <pdcurses/curses.h>

#include "./headers/TitleScreen.h"


int main(int argc, char* argv[])
{
    initscr();
    noecho();

    char title_screen_ch = NULL;
    int n_players = 2;

    while (1) {
        DisplayTitleScreen();
        title_screen_ch = getch();

        if (title_screen_ch == '1') {
            StartGame(n_players);
        }
        else if (title_screen_ch == '2') {
            n_players = DisplayOptionsScreen(n_players);
        }
        else if (title_screen_ch == '3') {
            ExitGame();
        }
    }

    refresh();
    getch();
    endwin();
    return 0;
}