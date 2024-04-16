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

void Cribbage::WDisplayEmptyColouredBoard(std::string board_name) {
	MVWPrintWColoured(board_win, coords["board"].at(0), coords["board"].at(1), cribbage_boards_coloured[board_name]);
}

void Cribbage::WDisplayTextArea() {
	WPrintWSAAtCoord(text_area_win, "text_area", { "Example for text window." });
}

void Cribbage::WDisplayPlayArea() {

	wattron(play_area_win, COLOR_PAIR(1));
	WPrintWSAAtCoord(play_area_win, "origin", { 6,0 }, ascii_deck_face_down);
	wattroff(play_area_win, COLOR_PAIR(1));

	WDisplayThePlayPile(
		{ 
			{"Ace", "Diamonds"},
			{"2", "Clubs"},
			{"5", "Spades"},
			{"6", "Hearts"}
		}
	);

	WDisplayPlayerHand(0);
	WDisplayPlayerHand(1);

	//WPrintWSAAtCoord(play_area_win, "origin", { 6,0 }, GenerateAsciiDeckFaceUp({"Jack","Clubs"}));
}

void Cribbage::WDisplayPlayerHand(int player_index) {

	if (player_index == 0) {
		WDisplayCard(play_area_win, "Ace", "Clubs", { 13,0 });
		WDisplayCard(play_area_win, "4", "Diamonds", { 13, 6 });
		WDisplayCard(play_area_win, "King", "Spades", { 13, 12 });
		WDisplayCard(play_area_win, "9", "Hearts", { 13, 18 });
		WDisplayCard(play_area_win, "3", "Spades", { 13, 24 });
		WDisplayCard(play_area_win, "Queen", "Diamonds", { 13, 30 });
	}
	else {
		wattron(play_area_win, COLOR_PAIR(1));
		WPrintWSAAtCoord(play_area_win, "origin", card_back);
		WPrintWSAAtCoord(play_area_win, "origin", { 0,6 }, card_back);
		WPrintWSAAtCoord(play_area_win, "origin", { 0,12 }, card_back);
		WPrintWSAAtCoord(play_area_win, "origin", { 0,18 }, card_back);
		WPrintWSAAtCoord(play_area_win, "origin", { 0,24 }, card_back);
		WPrintWSAAtCoord(play_area_win, "origin", { 0,30 }, card_back);
		wattroff(play_area_win, COLOR_PAIR(1));
	}
	
}

void Cribbage::WDisplayThePlayPile(std::vector <std::vector <std::string>> cards) {
	if (cards.size() == 1) {
		WDisplayCard(play_area_win, cards.at(0).at(0), cards.at(0).at(1), {6, 8});
	}
	else if (cards.size() > 1) {
		WDisplayCard(play_area_win, cards.back().at(0), cards.back().at(1), {6, 8 + 2 * (int(cards.size()) - 1)});

		for (int i = 0; i < cards.size() - 1; i++) {
			WDisplayPartialCard(play_area_win, cards.at(i).at(0), cards.at(i).at(1), { 6, 8 + 2*i });
		}
	}
}

void Cribbage::WDisplayCard(WINDOW* window, std::string value, std::string suit) {
	int n_colour_pair = 2;

	if ((suit == "Clubs") || (suit == "Spades")) {
		n_colour_pair = 1;
	}
	wattron(window, COLOR_PAIR(n_colour_pair));
	WPrintWSAAtCoord(window, "origin", ascii_cards["full"][value][suit]);
	wattroff(window, COLOR_PAIR(n_colour_pair));
}

void Cribbage::WDisplayCard(WINDOW* window, std::string value, std::string suit, std::vector<int> offset) {
	int n_colour_pair = 2;

	if ((suit == "Clubs") || (suit == "Spades")) {
		n_colour_pair = 1;
	}
	wattron(window, COLOR_PAIR(n_colour_pair));
	WPrintWSAAtCoord(window, "origin", offset, ascii_cards["full"][value][suit]);
	wattroff(window, COLOR_PAIR(n_colour_pair));
}

void Cribbage::WDisplayPartialCard(WINDOW* window, std::string value, std::string suit) {
	int n_colour_pair = 2;

	if ((suit == "Clubs") || (suit == "Spades")) {
		n_colour_pair = 1;
	}
	wattron(window, COLOR_PAIR(n_colour_pair));
	WPrintWSAAtCoord(window, "origin", ascii_cards["partial"][value][suit]);
	wattroff(window, COLOR_PAIR(n_colour_pair));
}

void Cribbage::WDisplayPartialCard(WINDOW* window, std::string value, std::string suit, std::vector<int> offset) {
	int n_colour_pair = 2;

	if ((suit == "Clubs") || (suit == "Spades")) {
		n_colour_pair = 1;
	}
	wattron(window, COLOR_PAIR(n_colour_pair));
	WPrintWSAAtCoord(window, "origin", offset, ascii_cards["partial"][value][suit]);
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
		MVWPrintWSA(
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
		MVWPrintWSA(
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
	//wrefresh(header_win);
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
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
}