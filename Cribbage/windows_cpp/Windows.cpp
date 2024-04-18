#include <string>
#include <vector>
#include <map>
#include "../headers/Windows.h"

WINDOW* CreateNewWin(std::vector<int> window_dims)
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

WINDOW* CreateNewWinBorder(std::vector<int> window_dims)
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

void DestroyWin(WINDOW* local_win)
{
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(local_win);
	delwin(local_win);
}

void MVPrintWSA(int y, int x, std::vector<std::string> texts)
{
	int i = 0;
	for (const std::string& text : texts) {
		mvprintw(y + i, x, text.c_str());
		i++;
	}
}

void MVWPrintWSA(WINDOW* window, int y, int x, std::vector<std::string> texts)
{
	int i = 0;
	for (const std::string& text : texts) {
		mvwprintw(window, y + i, x, text.c_str());
		i++;
	}
}

void MVWPrintWColoured(WINDOW* window, int y, int x, std::map<int, std::vector < std::string>> text_map)
{
	std::vector<int> keys;

	for (auto item : text_map) {
		keys.push_back(item.first);
	}

	for (int i = 0; i < text_map[keys.at(0)].size(); i++) {
		for (int j = 0; j < text_map[keys.at(0)].at(0).length(); j++) {
			for (int key : keys) {
				if (!std::isspace(text_map[key].at(i)[j])) {
					wattron(window, COLOR_PAIR(key));
					mvwprintw(window, y + i, x + j, &text_map[key].at(i)[j]);
					wattroff(window, COLOR_PAIR(key));
				}
			}
		}
	}
}