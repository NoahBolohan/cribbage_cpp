#include <stdlib.h>
#include <string>
#include <algorithm>
#include "../headers/TitleScreen.h"
#include "../headers/CribbageFunctions.h"

void DisplayTitleScreen(WINDOW* window, int title_screen_y) {
   wclear(window);
    if (title_screen_y == 0) {
        wattron(window, COLOR_PAIR(1));
        mvwprintw(window, 0, 0, "Start");
        wattroff(window, COLOR_PAIR(1));
        mvwprintw(window, 1, 0, "Options");
        mvwprintw(window, 2, 0, "Exit");
    }
    else if (title_screen_y == 1) {
        mvwprintw(window, 0, 0, "Start");
        wattron(window, COLOR_PAIR(1));
        mvwprintw(window, 1, 0, "Options");
        wattroff(window, COLOR_PAIR(1));
        mvwprintw(window, 2, 0, "Exit");
    }
    else if (title_screen_y == 2) {
        mvwprintw(window, 0, 0, "Start");
        mvwprintw(window, 1, 0, "Options");
        wattron(window, COLOR_PAIR(1));
        mvwprintw(window, 2, 0, "Exit");
        wattroff(window, COLOR_PAIR(1));
    }

    mvwprintw(window, 4, 0, "Navigate -- Arrow keys");
    mvwprintw(window, 5, 0, "Select -- Enter key");
}

void StartGame(int n_players, std::map<int, int> player_colour_map) {
    clear();
    Cribbage cribbage(n_players, player_colour_map);
    cribbage.StartGame();
}

std::tuple<int, std::map<int, int>> DisplayOptionsScreen(WINDOW* window, int n_players, std::map<int, int> colour_map) {

    char options_ch = NULL;
    int options_screen_y = 0;

    int n_players_option = n_players;

    std::map<int, int> player_colour_map = colour_map;

    while (1) {
        DisplayOptionsScreenOptions(window, options_screen_y);
  
        options_ch = wgetch(window);

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
                wmove(window, 2, 0);
                wclrtoeol(window);
                mvwprintw(window, 2, 0, "Number of players");
                n_players_option = DisplayNPlayerMenu(window, options_ch, n_players_option);
            }
            else if (options_screen_y == 1) {
                wmove(window, 4, 0);
                wclrtoeol(window);
                mvwprintw(window, 4, 0, "Player colours");
                player_colour_map = DisplayPlayerColoursMenu(window, options_ch, n_players_option, player_colour_map);
            }
            else if (options_screen_y == 2) {
                break;
            }
        }
    }

    return std::make_tuple(n_players_option, player_colour_map);
}

void DisplayOptionsScreenOptions(WINDOW* window, int options_screen_y) {
   wclear(window);
    if (options_screen_y == 0) {
        mvwprintw(window, 0, 0, "Options page");
        wattron(window, COLOR_PAIR(1));
        mvwprintw(window, 2, 0, "Number of players");
        wattroff(window, COLOR_PAIR(1));
        mvwprintw(window, 4, 0, "Player colours");
        mvwprintw(window, 9, 0, "Return to title screen");
    }
    else if (options_screen_y == 1) {
        mvwprintw(window, 0, 0, "Options page");
        mvwprintw(window, 2, 0, "Number of players");
        wattron(window, COLOR_PAIR(1));
        mvwprintw(window, 4, 0, "Player colours");
        wattroff(window, COLOR_PAIR(1));
        mvwprintw(window, 9, 0, "Return to title screen");
    }
    else if (options_screen_y == 2) {
        mvwprintw(window, 0, 0, "Options page");
        mvwprintw(window, 2, 0, "Number of players");
        mvwprintw(window, 4, 0, "Player colours");
        wattron(window, COLOR_PAIR(1));
        mvwprintw(window, 9, 0, "Return to title screen");
        wattroff(window, COLOR_PAIR(1));
    }

    mvwprintw(window, 11, 0, "Navigate -- Arrow keys");
    mvwprintw(window, 12, 0, "Select -- Enter key");
}

int DisplayNPlayerMenu(WINDOW* window, char options_ch, int n_players_option) {

    char n_player_menu_ch = NULL;
    int n_player_menu_x = n_players_option == 2 ? 0 : 1;

    while (1) {

        // Print n-player menu, coloured accordingly
        mvwprintw(window, 2, 17, ": ");
        if (n_players_option == 2) {

            wattron(window, COLOR_PAIR(1));
            mvwprintw(window, 3, 0, "2 players");
            wattroff(window, COLOR_PAIR(1));

            mvwprintw(window, 3, 9, ", ");

            mvwprintw(window, 3, 11, "3 players");
        }
        else if (n_players_option == 3) {

            mvwprintw(window, 3, 0, "2 players");

            mvwprintw(window, 3, 9, ", ");

            wattron(window, COLOR_PAIR(1));
            mvwprintw(window, 3, 11, "3 players");
            wattroff(window, COLOR_PAIR(1));
        }

        n_player_menu_ch = wgetch(window);

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
            wmove(window, 3, 0);
            wclrtoeol(window);
            break;
        }
    }

    return n_players_option;
}

std::map<int, int> DisplayPlayerColoursMenu(WINDOW* window, char options_ch, int n_players_option, std::map<int, int> player_colour_map) {

    char player_colours_menu_ch = NULL;
    int player_colours_menu_y = 0;
    int colour_idx;

    std::vector<int> unique_colour_choices;

    while (1) {

        // Print player colour menu, coloured accordingly
        mvwprintw(window, 4, 14, ":");

        if (player_colours_menu_y == 0) {
            wattron(window, COLOR_PAIR(1));
            mvwprintw(window, 5, 4, "Player 1: ");
            wattroff(window, COLOR_PAIR(1));
            mvwprintw(window, 6, 4, "Player 2: ");

            if (n_players_option == 3) {
                mvwprintw(window, 7, 4, "Player 3: ");
            }
        }
        else if (player_colours_menu_y == 1) {
            mvwprintw(window, 5, 4, "Player 1: ");
            wattron(window, COLOR_PAIR(1));
            mvwprintw(window, 6, 4, "Player 2: ");
            wattroff(window, COLOR_PAIR(1));
            if (n_players_option == 3) {
                mvwprintw(window, 7, 4, "Player 3: ");
            }
        }
        else if (player_colours_menu_y == 2) {
            mvwprintw(window, 5, 4, "Player 1: ");
            mvwprintw(window, 6, 4, "Player 2: ");
            wattron(window, COLOR_PAIR(1));
            mvwprintw(window, 7, 4, "Player 3: ");
            wattroff(window, COLOR_PAIR(1));
        }

        unique_colour_choices.clear();
        for (int i = 1; i <= n_players_option; i++) {
            unique_colour_choices.push_back(player_colour_map[i]);

            if (player_colour_map[i] == 0) {
                wmove(window, 4 + i, 14);
                wclrtoeol(window);
                wattron(window, COLOR_PAIR(2));
                mvwprintw(window, 4 + i, 14, "cyan");
                wattroff(window, COLOR_PAIR(2));
            }
            else if (player_colour_map[i] == 1) {
                wmove(window, 4 + i, 14);
                wclrtoeol(window);
                wattron(window, COLOR_PAIR(3));
                mvwprintw(window, 4 + i, 14, "red");
                wattroff(window, COLOR_PAIR(3));
            }
            else if (player_colour_map[i] == 2) {
                wmove(window, 4 + i, 14);
                wclrtoeol(window);
                wattron(window, COLOR_PAIR(4));
                mvwprintw(window, 4 + i, 14, "green");
                wattroff(window, COLOR_PAIR(4));
            }
            else if (player_colour_map[i] == 3) {
                wmove(window, 4 + i, 14);
                wclrtoeol(window);
                wattron(window, COLOR_PAIR(5));
                mvwprintw(window, 4 + i, 14, "magenta");
                wattroff(window, COLOR_PAIR(5));
            }
            else if (player_colour_map[i] == 4) {
                wmove(window, 4 + i, 14);
                wclrtoeol(window);
                wattron(window, COLOR_PAIR(6));
                mvwprintw(window, 4 + i, 14, "blue");
                wattroff(window, COLOR_PAIR(6));
            }
        }

        player_colours_menu_ch = wgetch(window);

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
            colour_idx = player_colour_map[player_colours_menu_y + 1];

            unique_colour_choices.erase(
                std::remove(
                    unique_colour_choices.begin(),
                    unique_colour_choices.end(),
                    colour_idx
                ),
                unique_colour_choices.end()
            );
            
            colour_idx = (colour_idx + 1) % 5;

            while (std::find(unique_colour_choices.begin(), unique_colour_choices.end(), colour_idx) != unique_colour_choices.end()) {
                colour_idx = (colour_idx + 1) % 5;
            }

            player_colour_map[player_colours_menu_y + 1] = colour_idx;
        }
        else if (player_colours_menu_ch == '\x4') {
            colour_idx = player_colour_map[player_colours_menu_y + 1];

            unique_colour_choices.erase(
                std::remove(
                    unique_colour_choices.begin(),
                    unique_colour_choices.end(),
                    colour_idx
                ),
                unique_colour_choices.end()
            );

            colour_idx = (colour_idx + 4) % 5;

            while (std::find(unique_colour_choices.begin(), unique_colour_choices.end(), colour_idx) != unique_colour_choices.end()) {
                colour_idx = (colour_idx + 4) % 5;
            }

            player_colour_map[player_colours_menu_y + 1] = colour_idx;
        }

        if (player_colours_menu_ch == '\n') {
            wmove(window, 5, 0);
            wclrtoeol(window);
            wmove(window, 6, 0);
            wclrtoeol(window);
            if (n_players_option == 3) {
                wmove(window, 7, 0);
                wclrtoeol(window);
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