#include "./headers/TitleScreen.h"


int main(int argc, char* argv[])
{
    WINDOW* menu_screen_border_window;
    WINDOW* menu_screen_window;

    initscr();
    curs_set(FALSE);

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_BLUE, COLOR_BLACK);

    char title_screen_ch = NULL;
    int title_screen_y = 0;
    int n_players = 2;

    std::map<int, int> player_colour_map = {
        {1, 0},
        {2, 1},
        {3, 2}
    };

    std::vector<int> menu_size = { 15, 24 };

    resize_term(menu_size.at(0), menu_size.at(1));
    menu_screen_window = CreateNewWin({ menu_size.at(0), menu_size.at(1), 0, 0 });
    menu_screen_border_window = CreateNewWinBorder({ menu_size.at(0), menu_size.at(1), 0, 0 });
    keypad(menu_screen_window, TRUE);
    
    while (1) {
        DisplayTitleScreen(menu_screen_window, title_screen_y);
        title_screen_ch = wgetch(menu_screen_window);

        // Scroll title screen highlighter
        if (title_screen_ch == '\x2') {
            title_screen_y = (title_screen_y + 1) % 3;
        }
        else if (title_screen_ch == '\x3') {
            title_screen_y = (title_screen_y +2) % 3;
        }

        // Select highlighted item
        if (title_screen_ch == '\n') {
            if (title_screen_y == 0) {
                StartGame(n_players, player_colour_map);
            }
            else if (title_screen_y == 1) {
                tie(n_players, player_colour_map) = DisplayOptionsScreen(menu_screen_window, n_players, player_colour_map);
            }
            else if (title_screen_y == 2) {
                ExitGame();
            }
        }
    }

    refresh();
    wgetch(menu_screen_window);
    endwin();
    return 0;
}