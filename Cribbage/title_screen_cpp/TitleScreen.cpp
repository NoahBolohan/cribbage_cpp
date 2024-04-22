#include <stdlib.h>
#include <string>
#include "../headers/TitleScreen.h"
#include "../headers/CribbageFunctions.h"

void DisplayTitleScreen() {
    clear();
    mvprintw(1, 1, "1. Start");
    mvprintw(2, 1, "2. Options");
    mvprintw(3, 1, "3. Exit");
}

void StartGame(int n_players) {
    clear();
    Cribbage cribbage(n_players);
    cribbage.StartGame();
}

int DisplayOptionsScreen(int n_players) {

    clear();
    int n_players_option = n_players;

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);

    mvprintw(0, 0, "Options page");
    mvprintw(2, 0, "1. Number of players");
    mvprintw(3, 0, "2. Return to title screen");

    char options_ch = NULL;
    int n_players_options_toggler = 0;

    while (1) {
        options_ch = getch();

        // Toggle n-player option menu
        if (options_ch == '1') {
            n_players_options_toggler = (n_players_options_toggler + 1) % 2;
        }
        else if (options_ch == '2') {
            break;
        }

        n_players_option = DisplayNPlayerMenu(options_ch, n_players_option, n_players_options_toggler);
    }

    return n_players_option;
}

int DisplayNPlayerMenu(char options_ch, int n_players_option, int n_players_options_toggler) {

    // If toggler on, display n-player menu
    if (n_players_options_toggler) {

        // Change n-player option
        if (n_players_options_toggler && options_ch == 'a') {
            n_players_option = 2;
        }
        else if (n_players_options_toggler && options_ch == 'b') {
            n_players_option = 3;
        }

        // Print n-player menu, coloured accordingly
        mvprintw(2, 20, ": ");
        if (n_players_options_toggler && n_players_option == 2) {

            attron(COLOR_PAIR(1));
            mvprintw(2, 22, "(a) 2 players");
            attroff(COLOR_PAIR(1));

            mvprintw(2, 35, ", ");

            mvprintw(2, 37, "(b) 3 players");
        }
        else if (n_players_options_toggler && n_players_option == 3) {

            mvprintw(2, 22, "(a) 2 players");

            mvprintw(2, 35, ", ");

            attron(COLOR_PAIR(1));
            mvprintw(2, 37, "(b) 3 players");
            attroff(COLOR_PAIR(1));
        }
        else {
            mvprintw(2, 22, "(a) 2 players");

            mvprintw(2, 35, ", ");

            mvprintw(2, 37, "(b) 3 players");
        }
    }
    else {
        move(2, 20);
        clrtoeol();
    }

    return n_players_option;
}

void ExitGame() {
    endwin();
    exit(1);
}