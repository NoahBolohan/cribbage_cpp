#include "./headers/TitleScreen.h"


int main(int argc, char* argv[])
{
    initscr();
    noecho();
    start_color();
    curs_set(FALSE);
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_BLUE, COLOR_BLACK);

    char title_screen_ch = NULL;
    int n_players = 2;
    std::map<int, std::string> player_colour_map = {
        {1, "cyan"},
        {2, "red"},
        {3, "green"}
    };

    while (1) {
        DisplayTitleScreen();
        title_screen_ch = getch();

        if (title_screen_ch == '1') {
            StartGame(n_players, player_colour_map);
        }
        else if (title_screen_ch == '2') {
            tie(n_players, player_colour_map) = DisplayOptionsScreen(n_players, player_colour_map);
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