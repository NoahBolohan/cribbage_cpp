#include <stdlib.h>
#include <string>
#include "../headers/TitleScreen.h"
#include "../headers/CribbageFunctions.h"

void DisplayTitleScreen(int title_screen_y) {
    clear();
    if (title_screen_y == 0) {
        attron(COLOR_PAIR(1));
        mvprintw(1, 1, "Start");
        attroff(COLOR_PAIR(1));
        mvprintw(2, 1, "Options");
        mvprintw(3, 1, "Exit");
    }
    else if (title_screen_y == 1) {
        mvprintw(1, 1, "Start");
        attron(COLOR_PAIR(1));
        mvprintw(2, 1, "Options");
        attroff(COLOR_PAIR(1));
        mvprintw(3, 1, "Exit");
    }
    else if (title_screen_y == 2) {
        mvprintw(1, 1, "Start");
        mvprintw(2, 1, "Options");
        attron(COLOR_PAIR(1));
        mvprintw(3, 1, "Exit");
        attroff(COLOR_PAIR(1));
    }

    mvprintw(5, 1, "Navigate -- Arrow keys");
    mvprintw(6, 1, "Select -- Enter key");
}

void StartGame(int n_players, std::map<int, int> player_colour_map) {
    clear();
    Cribbage cribbage(n_players, player_colour_map);
    cribbage.StartGame();
}

std::tuple<int, std::map<int, int>> DisplayOptionsScreen(int n_players, std::map<int, int> colour_map) {

    char options_ch = NULL;
    int options_screen_y = 0;

    int n_players_option = n_players;

    std::map<int, int> player_colour_map = colour_map;

    while (1) {
        DisplayOptionsScreenOptions(options_screen_y);
  
        options_ch = getch();

        // Scroll options screen highlighter
        if (options_ch == '\x2') {
            options_screen_y = (options_screen_y + 1) % 3;
        }
        else if (options_ch == '\x3') {
            options_screen_y = (options_screen_y + 2) % 3;
        }

        // Select highlighted item
        if (options_ch == '\n') {
            if (options_screen_y == 0) {
                move(2, 0);
                clrtoeol();
                mvprintw(2, 0, "Number of players");
                n_players_option = DisplayNPlayerMenu(options_ch, n_players_option);
            }
            else if (options_screen_y == 1) {
                move(3, 0);
                clrtoeol();
                mvprintw(3, 0, "Player colours");
                player_colour_map = DisplayPlayerColoursMenu(options_ch, n_players_option, player_colour_map);
            }
            else if (options_screen_y == 2) {
                break;
            }
        }
    }

    return std::make_tuple(n_players_option, player_colour_map);
}

void DisplayOptionsScreenOptions(int options_screen_y) {
    clear();
    if (options_screen_y == 0) {
        mvprintw(0, 0, "Options page");
        attron(COLOR_PAIR(1));
        mvprintw(2, 0, "Number of players");
        attroff(COLOR_PAIR(1));
        mvprintw(3, 0, "Player colours");
        mvprintw(8, 0, "Return to title screen");
    }
    else if (options_screen_y == 1) {
        mvprintw(0, 0, "Options page");
        mvprintw(2, 0, "Number of players");
        attron(COLOR_PAIR(1));
        mvprintw(3, 0, "Player colours");
        attroff(COLOR_PAIR(1));
        mvprintw(8, 0, "Return to title screen");
    }
    else if (options_screen_y == 2) {
        mvprintw(0, 0, "Options page");
        mvprintw(2, 0, "Number of players");
        mvprintw(3, 0, "Player colours");
        attron(COLOR_PAIR(1));
        mvprintw(8, 0, "Return to title screen");
        attroff(COLOR_PAIR(1));
    }

    mvprintw(12, 1, "Navigate -- Arrow keys");
    mvprintw(13, 1, "Select -- Enter key");
}

int DisplayNPlayerMenu(char options_ch, int n_players_option) {

    char n_player_menu_ch = NULL;
    int n_player_menu_x = n_players_option == 2 ? 0 : 1;

    while (1) {

        // Print n-player menu, coloured accordingly
        mvprintw(2, 17, ": ");
        if (n_players_option == 2) {

            attron(COLOR_PAIR(1));
            mvprintw(2, 19, "2 players");
            attroff(COLOR_PAIR(1));

            mvprintw(2, 28, ", ");

            mvprintw(2, 30, "3 players");
        }
        else if (n_players_option == 3) {

            mvprintw(2, 19, "2 players");

            mvprintw(2, 28, ", ");

            attron(COLOR_PAIR(1));
            mvprintw(2, 30, "3 players");
            attroff(COLOR_PAIR(1));
        }
        else {
            mvprintw(2, 19, "2 players");

            mvprintw(2, 28, ", ");

            mvprintw(2, 30, "3 players");
        }

        n_player_menu_ch = getch();

        if (n_player_menu_ch == '\x4' || n_player_menu_ch == '\x5') {
            n_player_menu_x = (n_player_menu_x + 1) % 2;
            if (n_player_menu_x == 0) {
                n_players_option = 2;
            }
            else {
                n_players_option = 3;
            }
        }

        if (n_player_menu_ch == '\n') {
            move(2, 20);
            clrtoeol();
            break;
        }
    }

    return n_players_option;
}

std::map<int, int> DisplayPlayerColoursMenu(char options_ch, int n_players_option, std::map<int, int> player_colour_map) {

    char player_colours_menu_ch = NULL;
    int player_colours_menu_y = 0;

    while (1) {

        // Print player colour menu, coloured accordingly
        mvprintw(3, 14, ":");

        if (player_colours_menu_y == 0) {
            attron(COLOR_PAIR(1));
            mvprintw(4, 4, "Player 1: ");
            attroff(COLOR_PAIR(1));
            mvprintw(5, 4, "Player 2: ");

            if (n_players_option == 3) {
                mvprintw(6, 4, "Player 3: ");
            }
        }
        else if (player_colours_menu_y == 1) {
            mvprintw(4, 4, "Player 1: ");
            attron(COLOR_PAIR(1));
            mvprintw(5, 4, "Player 2: ");
            attroff(COLOR_PAIR(1));
            if (n_players_option == 3) {
                mvprintw(6, 4, "Player 3: ");
            }
        }
        else if (player_colours_menu_y == 2) {
            mvprintw(4, 4, "Player 1: ");
            mvprintw(5, 4, "Player 2: ");
            attron(COLOR_PAIR(1));
            mvprintw(6, 4, "Player 3: ");
            attroff(COLOR_PAIR(1));
        }


        for (int i = 1; i <= n_players_option; i++) {
            if (player_colour_map[i] == 0) {
                move(3 + i, 14);
                clrtoeol();
                attron(COLOR_PAIR(2));
                mvprintw(3 + i, 14, "cyan");
                attroff(COLOR_PAIR(2));
            }
            else if (player_colour_map[i] == 1) {
                move(3 + i, 14);
                clrtoeol();
                attron(COLOR_PAIR(3));
                mvprintw(3 + i, 14, "red");
                attroff(COLOR_PAIR(3));
            }
            else if (player_colour_map[i] == 2) {
                move(3 + i, 14);
                clrtoeol();
                attron(COLOR_PAIR(4));
                mvprintw(3 + i, 14, "green");
                attroff(COLOR_PAIR(4));
            }
        }

        player_colours_menu_ch = getch();

        // Scroll player colours menu highlighter
        if (player_colours_menu_ch == '\x2') {
            if (n_players_option == 3) {
                player_colours_menu_y = (player_colours_menu_y + 1) % 3;
            }
            else {
                player_colours_menu_y = (player_colours_menu_y + 1) % 2;
            }
        }
        else if (player_colours_menu_ch == '\x3') {
            if (n_players_option == 3) {
                player_colours_menu_y = (player_colours_menu_y + 2) % 3;
            }
            else {
                player_colours_menu_y = (player_colours_menu_y + 1) % 2;
            }
        }

        if (player_colours_menu_ch == '\x5') {
            player_colour_map[player_colours_menu_y + 1] = (player_colour_map[player_colours_menu_y + 1] + 1) % 3;
        }
        else if (player_colours_menu_ch == '\x4') {
            player_colour_map[player_colours_menu_y + 1] = (player_colour_map[player_colours_menu_y + 1] + 2) % 3;
        }

        if (player_colours_menu_ch == '\n') {
            move(4, 0);
            clrtoeol();
            move(5, 0);
            clrtoeol();
            if (n_players_option == 3) {
                move(6, 0);
                clrtoeol();
            }
            break;
        }
    }

    return player_colour_map;
}

void ExitGame() {
    endwin();
    exit(1);
}