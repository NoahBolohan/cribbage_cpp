#include <string>
#include <vector>
#include <stdexcept>
#include "../headers/Windows.h"
#include "../headers/CribbageFunctions.h"

void Cribbage::WDisplayHeader() {
	WPrintWSAAtCoord(header_win, "header", header);
}

void Cribbage::WDisplayBoard() {
	WPrintWSAAtCoord(board_win, "board", cribbage_boards[board_name]);
}

void Cribbage::WDisplayEmptyColouredBoard() {
	MVWPrintWColoured(board_win, coords["board"].at(0), coords["board"].at(1), cribbage_boards_coloured[board_name]);
}

void Cribbage::WDisplayPeg(int player_index) {

	if (scores.at(player_index) > 0) {
		wattron(board_win, COLOR_PAIR(player_index + 1));
		mvwaddch(
			board_win,
			peg_coords[player_index].at(0),
			peg_coords[player_index].at(1),
			cribbage_boards_coloured[board_name][player_index + 1].at(peg_coords[player_index].at(0))[peg_coords[player_index].at(1)]
		);
		wattroff(board_win, COLOR_PAIR(player_index + 1));
	}

	peg_coords[player_index] = cribbage_boards_coloured_routes[board_name][player_index + 1].at(scores.at(player_index));

	wattron(board_win, COLOR_PAIR(player_index+1));
	mvwaddch(
		board_win,
		peg_coords[player_index].at(0),
		peg_coords[player_index].at(1),
		'O'
	);
	wattroff(board_win, COLOR_PAIR(player_index + 1));
}

void Cribbage::WDisplayTextArea() {
	WPrintWSAAtCoord(text_area_win, "text_area", { "Example for text window." });
}

void Cribbage::WDisplayPlayArea() {

	wattron(play_area_win, COLOR_PAIR(5));
	WPrintWSAAtCoord(play_area_win, "origin", { 6,0 }, ascii_deck_face_down);
	wattroff(play_area_win, COLOR_PAIR(5));

	WDisplayThePlayPile(
		{ 
			{"Ace", "Diamonds"},
			{"2", "Clubs"},
			{"5", "Spades"},
			{"6", "Hearts"}
		}
	);

	WDisplayPlayerHand(0);
	WDisplayPlayerHand(1, true);

	//WPrintWSAAtCoord(play_area_win, "origin", { 6,0 }, GenerateAsciiDeckFaceUp({"Jack","Clubs"}));
}

void Cribbage::WDisplayPlayerHand(int player_index, bool hide_cards) {

	if (hide_cards) {
		wattron(player_windows[player_index], COLOR_PAIR(5));
		WPrintWSAAtCoord(player_windows[player_index], "origin", card_back);
		WPrintWSAAtCoord(player_windows[player_index], "origin", { 0,6 }, card_back);
		WPrintWSAAtCoord(player_windows[player_index], "origin", { 0,12 }, card_back);
		WPrintWSAAtCoord(player_windows[player_index], "origin", { 0,18 }, card_back);
		WPrintWSAAtCoord(player_windows[player_index], "origin", { 0,24 }, card_back);
		WPrintWSAAtCoord(player_windows[player_index], "origin", { 0,30 }, card_back);
		wattroff(player_windows[player_index], COLOR_PAIR(5));
	}
	else {
		WDisplayCard(player_windows[player_index], "Ace", "Clubs");
		WDisplayCard(player_windows[player_index], "4", "Diamonds", { 0,6 });
		WDisplayCard(player_windows[player_index], "King", "Spades", { 0,12 });
		WDisplayCard(player_windows[player_index], "9", "Hearts", { 0,18 });
		WDisplayCard(player_windows[player_index], "3", "Spades", { 0,24 });
		WDisplayCard(player_windows[player_index], "Queen", "Diamonds", { 0,30 });
	}
	
}

void Cribbage::WDisplayThePlayPile(std::vector <std::vector <std::string>> cards) {
	if (cards.size() == 1) {
		WDisplayCard(play_area_win, cards.at(0).at(0), cards.at(0).at(1), {6, 7});
	}
	else if (cards.size() > 1) {
		WDisplayCard(play_area_win, cards.back().at(0), cards.back().at(1), {6, 7 + 2 * (int(cards.size()) - 1)});

		for (int i = 0; i < cards.size() - 1; i++) {
			WDisplayPartialCard(play_area_win, cards.at(i).at(0), cards.at(i).at(1), { 6, 7 + 2*i });
		}
	}
}

void Cribbage::WDisplayCrib(std::vector <std::vector <std::string>> cards) {
	for (int i = 0; i < cards.size(); i++) {
		WDisplayCard(play_area_win, cards.at(i).at(0), cards.at(i).at(1), { 6, 7 + 6 * i });
	}
}

void Cribbage::WDisplayCard(WINDOW* window, std::string value, std::string suit) {
	int n_colour_pair = 6;

	if ((suit == "Clubs") || (suit == "Spades")) {
		n_colour_pair = 5;
	}
	wattron(window, COLOR_PAIR(n_colour_pair));
	WPrintWSAAtCoord(window, "origin", ascii_cards["full"][value][suit]);
	wattroff(window, COLOR_PAIR(n_colour_pair));
}

void Cribbage::WDisplayCard(WINDOW* window, std::string value, std::string suit, std::vector<int> offset) {
	int n_colour_pair = 6;

	if ((suit == "Clubs") || (suit == "Spades")) {
		n_colour_pair = 5;
	}
	wattron(window, COLOR_PAIR(n_colour_pair));
	WPrintWSAAtCoord(window, "origin", offset, ascii_cards["full"][value][suit]);
	wattroff(window, COLOR_PAIR(n_colour_pair));
}

void Cribbage::WDisplayPartialCard(WINDOW* window, std::string value, std::string suit) {
	int n_colour_pair = 6;

	if ((suit == "Clubs") || (suit == "Spades")) {
		n_colour_pair = 5;
	}
	wattron(window, COLOR_PAIR(n_colour_pair));
	WPrintWSAAtCoord(window, "origin", ascii_cards["partial"][value][suit]);
	wattroff(window, COLOR_PAIR(n_colour_pair));
}

void Cribbage::WDisplayPartialCard(WINDOW* window, std::string value, std::string suit, std::vector<int> offset) {
	int n_colour_pair = 6;

	if ((suit == "Clubs") || (suit == "Spades")) {
		n_colour_pair = 5;
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
	wrefresh(player0_win);
	wrefresh(player1_win);
	wrefresh(player2_win);
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
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);
	init_pair(6, COLOR_RED, COLOR_WHITE);
	
}