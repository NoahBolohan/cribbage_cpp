#include <string>
#include <vector>
#include <stdexcept>
#include "../headers/Windows.h"
#include "../headers/CribbageFunctions.h"

void Cribbage::WDisplayWelcomeText() {
	WPrintWSAAtCoord(text_area_win, "text_area", welcome_text);
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

	peg_coords[player_index] = cribbage_boards_coloured_routes[board_name][player_index + 1].at(std::min(121, scores.at(player_index)));

	wattron(board_win, COLOR_PAIR(player_index+1));
	mvwaddch(
		board_win,
		peg_coords[player_index].at(0),
		peg_coords[player_index].at(1),
		'O'
	);
	wattroff(board_win, COLOR_PAIR(player_index + 1));

	refresh_wins({ board_win });
}

void Cribbage::WPrintToTextArea(std::vector<std::string> lines, bool append, std::string position) {

	if (append) {
		for (auto line : lines) {
			text_area_contents.push_back(line);
		}
		if (text_area_contents.size() > getmaxy(text_area_win)) {
			text_area_contents.erase(text_area_contents.begin(), text_area_contents.end() - getmaxy(text_area_win));
		}
	}
	else {
		text_area_contents = lines;
	}

	reset_win(text_area_win);
	if (position == "newline") {
		WPrintWSAAtCoord(text_area_win, "text_area", text_area_contents, "newline");
	}
	else {
		WPrintWSAAtCoord(text_area_win, "text_area", text_area_contents);
	}
	refresh_wins({ text_area_win });
}

void Cribbage::WDisplayInitialPlayArea() {

	wattron(play_area_win, COLOR_PAIR(5));
	WPrintWSAAtCoord(play_area_win, "origin", { 6,0 }, ascii_deck_face_down);
	wattroff(play_area_win, COLOR_PAIR(5));
	refresh_wins({ play_area_win });
}

void Cribbage::WDisplayPlayArea() {

	reset_win({ play_area_win });

	
	if (starter.size() == 2) {
		int n_colour_pair = 6;

		if ((starter.at(1) == "Clubs") || (starter.at(1) == "Spades")) {
			n_colour_pair = 5;
		}

		wattron(play_area_win, COLOR_PAIR(n_colour_pair));
		WPrintWSAAtCoord(play_area_win, "origin", { 6,0 }, GenerateAsciiDeckFaceUp(starter));
		wattroff(play_area_win, COLOR_PAIR(n_colour_pair));
	}
	else {
		wattron(play_area_win, COLOR_PAIR(5));
		WPrintWSAAtCoord(play_area_win, "origin", { 6,0 }, ascii_deck_face_down);
		wattroff(play_area_win, COLOR_PAIR(5));
	}
	

	WDisplayThePlayPile(deck.GetCommonPiles()["the_play"]);

	WDisplayPlayerHand(0);
	WDisplayPlayerHand(1, true);
	if (number_of_players == 3) {
		WDisplayPlayerHand(2, true);
	}

	refresh_wins({ play_area_win });
}

void Cribbage::WDisplayPlayerHand(int player_index, bool hide_cards) {

	reset_win({ player_windows[player_index] });

	if (hide_cards) {
		wattron(player_windows[player_index], COLOR_PAIR(5));
		for (int i = 0; i < deck.GetHands().at(player_index).size(); i++) {
			WPrintWSAAtCoord(player_windows[player_index], "origin", { 0,6*i }, card_back);
		}
		wattroff(player_windows[player_index], COLOR_PAIR(5));
	}
	else {
		for (int i = 0; i < deck.GetHands().at(player_index).size(); i++) {
			WDisplayCard(
				player_windows[player_index],
				deck.GetHands().at(player_index).at(i).at(0),
				deck.GetHands().at(player_index).at(i).at(1),
				{ 0,6*i }
			);

		}
	}

	if (player_index == 0) {
		for (int i = 0; i < deck.GetHands().at(player_index).size(); i++) {
			MVWPrintWSA(player_windows[player_index], 5, 1 + 6*i, { "(" + std::to_string(i) + ")" });
		}
	}
	
	refresh_wins({ player_windows[player_index] });
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
			coords[coord_name].at(0) + lines.size()-1,
			coords[coord_name].at(1) + lines.back().size()
		);
	}

	catch (const std::invalid_argument& e) {
		WPrintWAtCoord(text_area_win, "guess_text", e.what(), true);
		getch();
	}
}

void Cribbage::WPrintWSAAtCoord(WINDOW* window, std::string coord_name, std::vector<std::string> lines, std::string position) {
	try {
		if (coords.find(coord_name) == coords.end()) {
			throw std::invalid_argument(coord_name + " not in coords keys");
		}
		if (position == "newline") {
			if (lines.size() >= getmaxy(window)) {
				lines.erase(lines.begin(), lines.begin() + 1);

				MVWPrintWSA(
					window,
					coords[coord_name].at(0),
					coords[coord_name].at(1),
					lines
				);
				wmove(
					window,
					coords[coord_name].at(0) + lines.size(),
					0
				);
			}
			else {
				MVWPrintWSA(
					window,
					coords[coord_name].at(0),
					coords[coord_name].at(1),
					lines
				);
				wmove(
					window,
					coords[coord_name].at(0) + lines.size(),
					0
				);
			}
		}
		else {
			MVWPrintWSA(
				window,
				coords[coord_name].at(0),
				coords[coord_name].at(1),
				lines
			);
			wmove(
				window,
				coords[coord_name].at(0) + lines.size() - 1,
				coords[coord_name].at(1) + lines.back().size()
			);
		}
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