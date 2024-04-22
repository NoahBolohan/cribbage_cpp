#include <string>
#include <vector>
#include <stdexcept>
#include <cmath>
#include "../headers/Windows.h"
#include "../headers/CribbageFunctions.h"

void Cribbage::WDisplayWelcomeText() {

	std::vector<int> welcome_text_colours;
	for (auto line : welcome_text) {
		welcome_text_colours.push_back(0);
	}

	WPrintLines(text_area_win, welcome_text, welcome_text_colours, { 0, 0 }, "eol");
}

void Cribbage::WDisplayEmptyColouredBoard() {
	MVWPrintWColoured(board_win, 0, 0, cribbage_boards_coloured[board_name]);
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

void Cribbage::WDisplayInitialPlayArea() {

	std::vector<int> card_colours;
	for (auto line : ascii_deck_face_down) {
		card_colours.push_back(5);
	}
	WPrintLines(play_area_win, ascii_deck_face_down, card_colours, { (getmaxy(play_area_win) - 7) / 2,0}); // 21 -> 6

	refresh_wins({ play_area_win });
}

void Cribbage::WDisplayPlayArea() {

	reset_win({ play_area_win });

	
	if (starter.size() == 2) {
		int n_colour_pair = 6;

		if ((starter.at(1) == "Clubs") || (starter.at(1) == "Spades")) {
			n_colour_pair = 5;
		}

		std::vector<int> card_colours;
		for (auto line : ascii_deck_face_down) {
			card_colours.push_back(n_colour_pair);
		}
		WPrintLines(play_area_win, GenerateAsciiDeckFaceUp(starter), card_colours, { int((getmaxy(play_area_win) - 6) / 2), 0 });
	}
	else {
		std::vector<int> card_colours;
		for (auto line : ascii_deck_face_down) {
			card_colours.push_back(5);
		}
		WPrintLines(play_area_win, ascii_deck_face_down, card_colours, { int((getmaxy(play_area_win) - 6) / 2),0 });
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
	if (player_index == 2) {
		if (hide_cards) {
			std::vector<int> card_back_colours;
			for (auto line : card_back_hori) {
				card_back_colours.push_back(5);
			}
			for (int i = 0; i < deck.GetHands().at(player_index).size(); i++) {
				WPrintLines(player_windows[player_index], card_back_hori, card_back_colours, { 4 * i, 0 }, "");
			}
		}
		else {
			for (int i = 0; i < deck.GetHands().at(player_index).size(); i++) {
				WDisplayCard(
					player_windows[player_index],
					deck.GetHands().at(player_index).at(i).at(0),
					deck.GetHands().at(player_index).at(i).at(1),
					{ 0,6 * i }
				);

			}
		}
	}
	else {
		if (hide_cards) {
			std::vector<int> card_back_colours;
			for (auto line : card_back_vert) {
				card_back_colours.push_back(5);
			}
			for (int i = 0; i < deck.GetHands().at(player_index).size(); i++) {
				WPrintLines(player_windows[player_index], card_back_vert, card_back_colours, { 0, 6 * i }, "");
			}
		}
		else {
			for (int i = 0; i < deck.GetHands().at(player_index).size(); i++) {
				WDisplayCard(
					player_windows[player_index],
					deck.GetHands().at(player_index).at(i).at(0),
					deck.GetHands().at(player_index).at(i).at(1),
					{ 0,6 * i }
				);

			}
		}
	}
	

	if (player_index == 0) {
		for (int i = 0; i < deck.GetHands().at(player_index).size(); i++) {
			MVWPrintWSA(player_windows[player_index], 5, 1 + 6 * i, { "(" + std::to_string(i) + ")" }, { 0 });
		}
	}
	
	refresh_wins({ player_windows[player_index] });
}

void Cribbage::WDisplayThePlayPile(std::vector <std::vector <std::string>> cards) {
	if (cards.size() == 1) {
		WDisplayCard(play_area_win, cards.at(0).at(0), cards.at(0).at(1), { int((getmaxy(play_area_win) - 6) / 2), 7});
	}
	else if (cards.size() > 1) {
		WDisplayCard(play_area_win, cards.back().at(0), cards.back().at(1), { int((getmaxy(play_area_win) - 6) / 2), 7 + 2 * (int(cards.size()) - 1)});

		for (int i = 0; i < cards.size() - 1; i++) {
			WDisplayPartialCard(play_area_win, cards.at(i).at(0), cards.at(i).at(1), { int((getmaxy(play_area_win) - 6) / 2), 7 + 2*i });
		}
	}
}

void Cribbage::WDisplayCrib(std::vector <std::vector <std::string>> cards) {
	for (int i = 0; i < cards.size(); i++) {
		WDisplayCard(play_area_win, cards.at(i).at(0), cards.at(i).at(1), { 6, 7 + 6 * i });
	}
}

void Cribbage::WDisplayCard(WINDOW* window, std::string value, std::string suit, std::vector<int> offset) {
	int n_colour_pair = 6;

	if ((suit == "Clubs") || (suit == "Spades")) {
		n_colour_pair = 5;
	}
	std::vector<int> card_colours;
	for (auto line : card_back_vert) {
		card_colours.push_back(n_colour_pair);
	}
	WPrintLines(window, ascii_cards["full"][value][suit], card_colours, offset);
}

void Cribbage::WDisplayPartialCard(WINDOW* window, std::string value, std::string suit, std::vector<int> offset) {
	int n_colour_pair = 6;

	if ((suit == "Clubs") || (suit == "Spades")) {
		n_colour_pair = 5;
	}
	std::vector<int> card_colours;
	for (auto line : card_back_vert) {
		card_colours.push_back(n_colour_pair);
	}
	WPrintLines(window, ascii_cards["partial"][value][suit], card_colours, offset);
}

void Cribbage::WPrintToTextArea(std::vector<std::string> lines, bool append, int colour_pair, std::string align, std::string position) {

	if (align == "right") {
		for (int i = 0; i < int(lines.size()); i++) {
			lines.at(i).insert(0, getmaxx(text_area_win) - int(lines.at(i).size()), ' ');
		}
	}

	if (align == "center") {
		for (int i = 0; i < int(lines.size()); i++) {
			lines.at(i).insert(0, int(std::floor(0.5 * (getmaxx(text_area_win) - int(lines.at(i).size())))), ' ');
			lines.at(i).insert(lines.at(i).end(), int(std::ceil(0.5 * (getmaxx(text_area_win) - int(lines.at(i).size())))), ' ');
		}
	}

	if (append) {
		for (auto line : lines) {
			text_area_contents.push_back(line);
			text_area_colours.push_back(colour_pair);
		}
		if (text_area_contents.size() > getmaxy(text_area_win)) {
			text_area_contents.erase(text_area_contents.begin(), text_area_contents.end() - getmaxy(text_area_win));
			text_area_colours.erase(text_area_colours.begin(), text_area_colours.end() - getmaxy(text_area_win));
		}
	}
	else {
		text_area_contents = lines;
		text_area_colours.clear();
		for (auto line : text_area_contents) {
			text_area_colours.push_back(colour_pair);
		}
	}

	reset_win(text_area_win);
	WPrintLines(text_area_win, text_area_contents, text_area_colours, { 0, 0 }, position);
	refresh_wins({ text_area_win });
}

void Cribbage::WPrintToTextArea(std::string line, bool append, int colour_pair, std::string align, std::string position) {

	if (align == "right") {
		line.insert(0, getmaxx(text_area_win) - int(line.size()), ' ');
	}

	if (align == "center") {
		line.insert(0, int(std::floor(0.5*(getmaxx(text_area_win) - int(line.size())))), ' ');
		line.insert(line.end(), int(std::ceil(0.5 * (getmaxx(text_area_win) - int(line.size())))), ' ');
	}

	if (append) {
		text_area_contents.push_back(line);
		text_area_colours.push_back(colour_pair);
		if (text_area_contents.size() > getmaxy(text_area_win)) {
			text_area_contents.erase(text_area_contents.begin(), text_area_contents.end() - getmaxy(text_area_win));
			text_area_colours.erase(text_area_colours.begin(), text_area_colours.end() - getmaxy(text_area_win));
		}
	}
	else {
		text_area_contents = { line };
		text_area_colours = { colour_pair };
	}

	reset_win(text_area_win);
	WPrintLines(text_area_win, text_area_contents, text_area_colours, { 0, 0 }, position);
	refresh_wins({ text_area_win });
}

void Cribbage::WPrintLine(WINDOW* window, std::string line, int colour, bool clear_line, std::vector<int> offset) {
	if (clear_line) {
		wmove(
			window,
			offset.at(0),
			offset.at(1)
		);
		wclrtoeol(window);
	}

	wattron(window, COLOR_PAIR(colour));
	mvwprintw(
		window,
		offset.at(0),
		offset.at(1),
		line.c_str()
	);
	wattroff(window, COLOR_PAIR(colour));
	wmove(
		window,
		offset.at(0),
		offset.at(1) + int(line.size())
	);
}

void Cribbage::WPrintLines(WINDOW* window, std::vector<std::string> lines, std::vector<int> colours, std::vector<int> offset, std::string position) {
	if (position == "newline") {
		if (lines.size() >= getmaxy(window)) {
			lines.erase(lines.begin(), lines.begin() + 1);
			colours.erase(colours.begin(), colours.begin() + 1);

			MVWPrintWSA(
				window,
				offset.at(0),
				offset.at(1),
				lines,
				colours
			);
			wmove(
				window,
				offset.at(0) + int(lines.size()),
				0
			);
		}
		else {
			MVWPrintWSA(
				window,
				offset.at(0),
				offset.at(1),
				lines,
				colours
			);
			wmove(
				window,
				offset.at(0) + int(lines.size()),
				0
			);
		}
	}
	else {
		MVWPrintWSA(
			window,
			offset.at(0),
			offset.at(1),
			lines,
			colours
		);
		wmove(
			window,
			offset.at(0) + int(lines.size() - 1),
			offset.at(1) + int(lines.back().size())
		);
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

void Cribbage::ResizeTerminal() {
	resize_term(
		window_dims["terminal"].at(0),
		window_dims["terminal"].at(1)
	);

	refresh();
}