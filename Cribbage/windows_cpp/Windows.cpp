#include <string>
#include <vector>
#include "../headers/Windows.h"
#include <pdcurses/curses.h>

WINDOW* create_newwin(std::vector<int> window_dims)
{
	int height = window_dims.at(0) - 2;
	int width = window_dims.at(1) - 2;
	int starty = window_dims.at(2) + 1;
	int startx = window_dims.at(3) + 1;

	WINDOW* local_win;

	local_win = newwin(height, width, starty, startx);
	wrefresh(local_win);
	return local_win;
}

WINDOW* create_newwin_border(std::vector<int> window_dims)
{
	int height = window_dims.at(0);
	int width = window_dims.at(1);
	int starty = window_dims.at(2);
	int startx = window_dims.at(3);

	WINDOW* local_win;

	local_win = newwin(height, width, starty, startx);
	wborder(local_win, '|', '|', '-', '-', '*', '+', '+', '+');
	wrefresh(local_win);
	return local_win;
}

void destroy_win(WINDOW* local_win)
{
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(local_win);
	delwin(local_win);
}

void mvprintw_sa(int y, int x, std::vector<std::string> texts)
{
	int i = 0;
	for (const std::string& text : texts) {
		mvprintw(y + i, x, text.c_str());
		i++;
	}
}

void mvwprintw_sa(WINDOW* window, int y, int x, std::vector<std::string> texts)
{
	int i = 0;
	for (const std::string& text : texts) {
		mvwprintw(window, y + i, x, text.c_str());
		i++;
	}
}