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

void StartGame(int n_players, std::map<int, std::string> player_colour_map) {
    clear();
    Cribbage cribbage(n_players, player_colour_map);
    cribbage.StartGame();
}

std::tuple<int, std::map<int, std::string>> DisplayOptionsScreen(int n_players, std::map<int, std::string> colour_map) {

    clear();

    mvprintw(0, 0, "Options page");
    mvprintw(2, 0, "1. Number of players");
    mvprintw(3, 0, "2. Player colours");
    mvprintw(8, 0, "3. Return to title screen");

    int n_players_options_toggler = 0;
    int n_players_option = n_players;

    int player_colour_options_toggler = 0;
    std::map<int, std::string> player_colour_map = colour_map;

    char options_ch = NULL;
    while (1) {
        options_ch = getch();

        // Toggle n-player option menu
        if (options_ch == '1') {
            n_players_options_toggler = (n_players_options_toggler + 1) % 2;
        }
        else if (options_ch == '2') {
            player_colour_options_toggler = (player_colour_options_toggler + 1) % 2;
        }
        else if (options_ch == '3') {
            break;
        }

        n_players_option = DisplayNPlayerMenu(options_ch, n_players_option, n_players_options_toggler);
        player_colour_map = DisplayPlayerColoursMenu(options_ch, player_colour_map, player_colour_options_toggler);
    }

    return std::make_tuple(n_players_option, player_colour_map);
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

std::map<int, std::string> DisplayPlayerColoursMenu(char options_ch, std::map<int, std::string> player_colour_map, int player_colour_options_toggler) {
    // If toggler on, display player colour menu
    if (player_colour_options_toggler) {

        // Change n-player option
        if (player_colour_options_toggler && options_ch == 'c') {
            player_colour_map[1] = "cyan";
        }
        else if (player_colour_options_toggler && options_ch == 'd') {
            player_colour_map[1] = "red";
        }
        else if (player_colour_options_toggler && options_ch == 'e') {
            player_colour_map[1] = "green";
        }
        else if (player_colour_options_toggler && options_ch == 'f') {
            player_colour_map[2] = "cyan";
        }
        else if (player_colour_options_toggler && options_ch == 'g') {
            player_colour_map[2] = "red";
        }
        else if (player_colour_options_toggler && options_ch == 'h') {
            player_colour_map[2] = "green";
        }
        else if (player_colour_options_toggler && options_ch == 'i') {
            player_colour_map[3] = "cyan";
        }
        else if (player_colour_options_toggler && options_ch == 'j') {
            player_colour_map[3] = "red";
        }
        else if (player_colour_options_toggler && options_ch == 'k') {
            player_colour_map[3] = "green";
        }

        // Print player colour menu, coloured accordingly
        mvprintw(3, 17, ":");
        if (player_colour_options_toggler && player_colour_map[1] == "cyan") {
            mvprintw(4, 4, "Player 1 (you): ");
            attron(COLOR_PAIR(2));
            mvprintw(4, 20, "(c) cyan");
            attroff(COLOR_PAIR(2));
            mvprintw(4, 28, ", ");
            mvprintw(4, 30, "(d) red");
            mvprintw(4, 37, ", ");
            mvprintw(4, 39, "(e) green");
        }
        else if (player_colour_options_toggler && player_colour_map[1] == "red") {
            mvprintw(4, 4, "Player 1 (you): ");
            mvprintw(4, 20, "(c) cyan");
            mvprintw(4, 28, ", ");
            attron(COLOR_PAIR(3));
            mvprintw(4, 30, "(d) red");
            attroff(COLOR_PAIR(3));
            mvprintw(4, 37, ", ");
            mvprintw(4, 39, "(e) green");
        }
        else if (player_colour_options_toggler && player_colour_map[1] == "green") {
            mvprintw(4, 4, "Player 1 (you): ");
            mvprintw(4, 20, "(c) cyan");
            mvprintw(4, 28, ", ");
            mvprintw(4, 30, "(d) red");
            mvprintw(4, 37, ", ");
            attron(COLOR_PAIR(4));
            mvprintw(4, 39, "(e) green");
            attroff(COLOR_PAIR(4));
        }

        if (player_colour_options_toggler && player_colour_map[2] == "cyan") {
            mvprintw(5, 4, "Player 2:       ");
            attron(COLOR_PAIR(2));
            mvprintw(5, 20, "(f) cyan");
            attroff(COLOR_PAIR(2));
            mvprintw(5, 28, ", ");
            mvprintw(5, 30, "(g) red");
            mvprintw(5, 37, ", ");
            mvprintw(5, 39, "(h) green");
        }
        else if (player_colour_options_toggler && player_colour_map[2] == "red") {
            mvprintw(5, 4, "Player 2:       ");
            mvprintw(5, 20, "(f) cyan");
            mvprintw(5, 28, ", ");
            attron(COLOR_PAIR(3));
            mvprintw(5, 30, "(g) red");
            attroff(COLOR_PAIR(3));
            mvprintw(5, 37, ", ");
            mvprintw(5, 39, "(h) green");
        }
        else if (player_colour_options_toggler && player_colour_map[2] == "green") {
            mvprintw(5, 4, "Player 2:       ");
            mvprintw(5, 20, "(f) cyan");
            mvprintw(5, 28, ", ");
            mvprintw(5, 30, "(g) red");
            mvprintw(5, 37, ", ");
            attron(COLOR_PAIR(4));
            mvprintw(5, 39, "(h) green");
            attroff(COLOR_PAIR(4));
        }
        
        if (player_colour_options_toggler && player_colour_map[3] == "cyan") {
            mvprintw(6, 4, "Player 3:       ");
            attron(COLOR_PAIR(2));
            mvprintw(6, 20, "(i) cyan");
            attroff(COLOR_PAIR(2));
            mvprintw(6, 28, ", ");
            mvprintw(6, 30, "(j) red");
            mvprintw(6, 37, ", ");
            mvprintw(6, 39, "(k) green");
        }
        else if (player_colour_options_toggler && player_colour_map[3] == "red") {
            mvprintw(6, 4, "Player 3:       ");
            mvprintw(6, 20, "(i) cyan");
            mvprintw(6, 28, ", ");
            attron(COLOR_PAIR(3));
            mvprintw(6, 30, "(j) red");
            attroff(COLOR_PAIR(3));
            mvprintw(6, 37, ", ");
            mvprintw(6, 39, "(k) green");
        }
        else if (player_colour_options_toggler && player_colour_map[3] == "green") {
            mvprintw(6, 4, "Player 3:       ");
            mvprintw(6, 20, "(i) cyan");
            mvprintw(6, 28, ", ");
            mvprintw(6, 30, "(j) red");
            mvprintw(6, 37, ", ");
            attron(COLOR_PAIR(4));
            mvprintw(6, 39, "(k) green");
            attroff(COLOR_PAIR(4));
        }
    }
    else {
        move(3, 17);
        clrtoeol();
        move(4, 0);
        clrtoeol();
        move(5, 0);
        clrtoeol();
        move(6, 0);
        clrtoeol();
    }

    return player_colour_map;
}

void ExitGame() {
    endwin();
    exit(1);
}