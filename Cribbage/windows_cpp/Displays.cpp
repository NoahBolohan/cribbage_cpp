#include <string>
#include <vector>
#include <stdexcept>
#include "../headers/Windows.h"
#include "../headers/CribbageFunctions.h"

void Cribbage::WDisplayHeader() {
	WPrintWSAAtCoord(header_win, "header", header);
}

void Cribbage::WDisplayBoard(std::string board_name) {
	WPrintWSAAtCoord(board_win, "board", cribbage_boards[board_name]);
}

void Cribbage::WDisplayTextArea() {
	WPrintWSAAtCoord(text_area_win, "text_area", { "Example for text window." });
}

void Cribbage::WDisplayPlayArea() {
	WDisplayCard(play_area_win, "Ace", "Clubs");
	WDisplayCard(play_area_win, "4", "Diamonds", { 0, 5 });
	WDisplayCard(play_area_win, "King", "Spades", { 0, 10 });
	WDisplayCard(play_area_win, "9", "Hearts", { 0, 15 });
	WDisplayCard(play_area_win, "3", "Spades", { 0, 20 });
	WDisplayCard(play_area_win, "Queen", "Diamonds", { 0, 25 });

	WDisplayCard(play_area_win, "Ace", "Clubs", { 6,0 });
	WDisplayCard(play_area_win, "4", "Diamonds", { 6, 5 });
	WDisplayCard(play_area_win, "King", "Spades", { 6, 10 });
	WDisplayCard(play_area_win, "9", "Hearts", { 6, 15 });
	WDisplayCard(play_area_win, "3", "Spades", { 6, 20 });
	WDisplayCard(play_area_win, "Queen", "Diamonds", { 6, 25 });
}


void Cribbage::WDisplayCard(WINDOW* window, std::string value, std::string suit) {
	int n_colour_pair = 2;

	if ((suit == "Clubs") || (suit == "Spades")) {
		n_colour_pair = 1;
	}
	wattron(window, COLOR_PAIR(n_colour_pair));
	WPrintWSAAtCoord(window, "origin", ascii_deck[value][suit]);
	wattroff(window, COLOR_PAIR(n_colour_pair));
}

void Cribbage::WDisplayCard(WINDOW* window, std::string value, std::string suit, std::vector<int> offset) {
	int n_colour_pair = 2;

	if ((suit == "Clubs") || (suit == "Spades")) {
		n_colour_pair = 1;
	}
	wattron(window, COLOR_PAIR(n_colour_pair));
	WPrintWSAAtCoord(window, "origin", offset, ascii_deck[value][suit]);
	wattroff(window, COLOR_PAIR(n_colour_pair));
}

void Cribbage::WPrintWAtCoord(WINDOW* window, std::string coord_name, std::string line, bool clear_line) {
	try {
		if (coords.find(coord_name) == coords.end()) {
			throw std::invalid_argument(coord_name + " not in coords keys");
		}
		if (clear_line) {
			wmove(
				window,
				coords[coord_name].at(0),
				coords[coord_name].at(1)
			);
			wclrtoeol(window);
		}

		mvwprintw(
			window,
			coords[coord_name].at(0),
			coords[coord_name].at(1),
			line.c_str()
		);
		wmove(
			window,
			coords[coord_name].at(0),
			coords[coord_name].at(1) + line.size()
		);
	}

	catch (const std::invalid_argument& e) {
		WPrintWAtCoord(text_area_win, "guess_text", e.what(), true);
		getch();
	}

}

void Cribbage::WPrintWAtCoord(WINDOW* window, std::string coord_name, std::vector<int> offset, std::string line, bool clear_line) {
	try {
		if (coords.find(coord_name) == coords.end()) {
			throw std::invalid_argument(coord_name + " not in coords keys");
		}
		if (clear_line) {
			wmove(
				window,
				coords[coord_name].at(0) + offset.at(0),
				coords[coord_name].at(1) + offset.at(1)
			);
			wclrtoeol(window);
		}

		mvwprintw(
			window,
			coords[coord_name].at(0) + offset.at(0),
			coords[coord_name].at(1) + offset.at(1),
			line.c_str()
		);
		wmove(
			window,
			coords[coord_name].at(0) + offset.at(0),
			coords[coord_name].at(1) + offset.at(1) + line.size()
		);
	}

	catch (const std::invalid_argument& e) {
		WPrintWAtCoord(text_area_win, "guess_text", e.what(), true);
		getch();
	}
}

void Cribbage::WPrintWSAAtCoord(WINDOW* window, std::string coord_name, std::vector<std::string> lines) {
	try {
		if (coords.find(coord_name) == coords.end()) {
			throw std::invalid_argument(coord_name + " not in coords keys");
		}
		mvwprintw_sa(
			window,
			coords[coord_name].at(0),
			coords[coord_name].at(1),
			lines
		);
		wmove(
			window,
			coords[coord_name].at(0) + lines.size(),
			coords[coord_name].at(1) + lines.back().size()
		);
	}

	catch (const std::invalid_argument& e) {
		WPrintWAtCoord(text_area_win, "guess_text", e.what(), true);
		getch();
	}
}

void Cribbage::WPrintWSAAtCoord(WINDOW* window, std::string coord_name, std::vector<int> offset, std::vector<std::string> lines) {
	try {
		if (coords.find(coord_name) == coords.end()) {
			throw std::invalid_argument(coord_name + " not in coords keys");
		}
		mvwprintw_sa(
			window,
			coords[coord_name].at(0) + offset.at(0),
			coords[coord_name].at(1) + offset.at(1),
			lines
		);
		wmove(
			window,
			coords[coord_name].at(0) + offset.at(0) + lines.size(),
			coords[coord_name].at(1) + offset.at(1) + lines.back().size()
		);
	}

	catch (const std::invalid_argument& e) {
		WPrintWAtCoord(text_area_win, "guess_text", e.what(), true);
		getch();
	}
}

void Cribbage::refresh_wins() {
	wrefresh(board_win);
	wrefresh(header_win);
	wrefresh(text_area_win);
	wrefresh(play_area_win);
}

void Cribbage::refresh_wins(std::vector<WINDOW*> wins_to_refresh) {
	for (auto win : wins_to_refresh) {
		wrefresh(win);
	}
}

void Cribbage::reset_win(WINDOW* window) {
	werase(window);
	wrefresh(window);
}

void Cribbage::GenerateColourPairs() {
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_RED, COLOR_WHITE);
}