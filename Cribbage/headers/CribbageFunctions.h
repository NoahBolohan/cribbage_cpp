#ifndef CRIBBAGE_HEADER
#define CRIBBAGE_HEADER

#include <string>
#include <vector>
#include <map>
#include "DeckFunctions.h"
#include <pdcurses/curses.h>

class Deck;

class Cribbage {
	public:
		// Game processes
		Cribbage(int, std::string, std::map<std::string, std::vector<int>>);

		void StartGame();
		void InitializeScores();
		void Round();
		void InitializePiles();
		void Deal();
		void DrawStarter();
		void ThePlay();
		void UpTo31();
		void TheShow();
		void EndGame();

		// Points
		void ThePlayPoints();
		void GoPoints();
		void TheShowPoints(int, std::vector<std::vector<std::string>>);

		void AddPoints(int, int, std::string);
		void AnnouncePoints(int, std::string);

		// Score-checking
		bool CheckFlush(std::vector<std::vector<std::string>>, int, std::string);
		bool CheckPairs(std::vector<std::vector<std::string>>, int, std::string);
		bool CheckRuns(std::vector<std::vector<std::string>>, int, std::string);
		
		void CheckRunsForShow(std::vector<std::vector<std::string>>);
		void CheckPairsForShow(std::vector<std::vector<std::string>>);
		void CheckFlushForShow(std::vector<std::vector<std::string>>);
		
		// ASCII
		void GenerateWelcomeText();
		void GenerateBoard();
		void GenerateDeck();
		void GenerateCardAsciis();
		std::vector<std::string> GenerateAsciiDeckFaceUp(std::vector < std::string>);

		// Display
		void WDisplayWelcomeText();
		void WDisplayBoard();
		void WDisplayEmptyColouredBoard();
		void WDisplayPeg(int);
		void WDisplayPlayArea();
		void WDisplayInitialPlayArea();
		void WDisplayPlayerHand(int, bool hide_cards = false);
		void WDisplayThePlayPile(std::vector <std::vector <std::string>>);
		void WDisplayCrib(std::vector <std::vector <std::string>>);
		void WDisplayCard(WINDOW*, std::string, std::string, std::vector<int> offset = { 0,0 });
		void WDisplayPartialCard(WINDOW*, std::string, std::string, std::vector<int> offset = { 0,0 });

		void WPrintToTextArea(std::vector<std::string>, bool append = false, std::string position = "eol");
		void WPrintToTextArea(std::string, bool append = false, std::string position = "eol");
		void WPrintLine(WINDOW*, std::string, bool clear_line = true, std::vector<int> offset = { 0,0 });
		void WPrintLines(WINDOW*, std::vector<std::string>, std::vector<int> offset = { 0,0 }, std::string position = "newline");

		void refresh_wins();
		void refresh_wins(std::vector<WINDOW*>);
		void reset_win(WINDOW*);
		void GenerateColourPairs();

		// Getters
		WINDOW* GetTextAreaWin();

		// Misc
		void RemovePlayerFromThePlay(int);
		void RemovePlayerFrom31(int);
		void PassToCrib(std::vector<std::vector<std::string>>);
		std::vector<std::vector<std::string>> GetCardsFromEnd(std::vector<std::vector<std::string>>, int);

	private:
		int number_of_players;

		Deck deck;
		
		std::vector<int> scores;
		std::vector<int> active_player_indices_for_play;
		std::vector<int> active_player_indices_for_31;
		std::vector<std::string> starter;
		const std::vector<std::string> side_pile_names = { 
			"the_play"
		};
		const std::vector<std::string> common_pile_names = {
			"crib",
			"the_play"
		};
		const int score_target = 121;

		bool game_over = false;

		int n_round = 1;
		int play_total = 0;
		int dealer = 0;
		int user_index = 0;


		// Maps
		std::map<std::string, int> card_value_points = {
			{"Ace", 1},
			{"2", 2},
			{"3", 3},
			{"4", 4},
			{"5", 5},
			{"6", 6},
			{"7", 7},
			{"8", 8},
			{"9", 9},
			{"10", 10},
			{"Jack", 10},
			{"Queen", 10},
			{"King", 10}
		};

		std::map<std::string, int> run_ordering = {
			{"Ace", 0},
			{"2", 1},
			{"3", 2},
			{"4", 3},
			{"5", 4},
			{"6", 5},
			{"7", 6},
			{"8", 7},
			{"9", 8},
			{"10", 9},
			{"Jack", 10},
			{"Queen", 11},
			{"King", 12}
		};

		WINDOW* board_border_win;
		WINDOW* text_area_border_win;
		WINDOW* play_area_border_win;

		WINDOW* board_win;
		WINDOW* text_area_win;
		WINDOW* play_area_win;

		WINDOW* player0_win;
		WINDOW* player1_win;
		WINDOW* player2_win;

		std::map<int, WINDOW*> player_windows;

		std::map < std::string, std::vector<int> > coords = {
			{"origin", {0, 0}},
			{"board", {0, 0}},
			{"text_area", {0, 0}},
			{"play_area", {0, 0}}
		};

		std::map < int, std::vector<int>> peg_coords;

		// ASCII members
		std::string board_name;
		std::map<std::string, std::vector < std::string>> cribbage_boards;
		std::map<std::string, std::map<int, std::vector < std::string>>> cribbage_boards_coloured;
		std::map<std::string, std::map<int, std::vector < std::vector<int>>>> cribbage_boards_coloured_routes;
		std::vector<std::string> welcome_text;
		std::vector<std::string> text_area_contents;
		std::map<std::string, std::map<std::string, std::map<std::string, std::vector<std::string>>>> ascii_cards;
		std::vector<std::string> card_back;
		std::vector<std::string> ascii_deck_face_down;

};

#endif