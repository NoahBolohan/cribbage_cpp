#ifndef CRIBBAGE_HEADER
#define CRIBBAGE_HEADER

#include <string>
#include <vector>
#include <map>
#include "DeckFunctions.h"
#include <pdcurses/curses.h>

class Cribbage {
	public:
		// Game processes
		Cribbage(int, std::map<std::string, std::vector<int>>);

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
		void DisplayScore();

		// Score-checking
		bool CheckFlush(std::vector<std::vector<std::string>>, int, std::string);
		bool CheckPairs(std::vector<std::vector<std::string>>, int, std::string);
		bool CheckRuns(std::vector<std::vector<std::string>>, int, std::string);
		
		void CheckRunsForShow(std::vector<std::vector<std::string>>);
		void CheckPairsForShow(std::vector<std::vector<std::string>>);
		void CheckFlushForShow(std::vector<std::vector<std::string>>);
		
		// ASCII
		void GenerateHeader();
		void GenerateBoard();
		void GenerateDeck();

		// Display
		void WDisplayHeader();
		void WDisplayBoard(std::string);
		void WDisplayColouredBoard(std::string);
		void WDisplayTextArea();
		void WDisplayPlayArea();
		void WDisplayCard(WINDOW*, std::string, std::string);
		void WDisplayCard(WINDOW*, std::string, std::string, std::vector<int>);
		void WPrintWAtCoord(WINDOW*, std::string, std::string, bool);
		void WPrintWAtCoord(WINDOW*, std::string, std::vector<int>, std::string, bool);
		void WPrintWSAAtCoord(WINDOW*, std::string, std::vector<std::string>);
		void WPrintWSAAtCoord(WINDOW*, std::string, std::vector<int>, std::vector<std::string>);
		void refresh_wins();
		void refresh_wins(std::vector<WINDOW*>);
		void reset_win(WINDOW*);
		void GenerateColourPairs();

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
		const int score_target = 40;

		bool game_over = false;

		int n_round = 1;
		int play_total = 0;
		int dealer = 0;
		int user_index = 0;

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

		WINDOW* header_border_win;
		WINDOW* board_border_win;
		WINDOW* text_area_border_win;
		WINDOW* play_area_border_win;

		WINDOW* header_win;
		WINDOW* board_win;
		WINDOW* text_area_win;
		WINDOW* play_area_win;

		std::map < std::string, std::vector<int> > coords = {
			{"origin", {0, 0}},
			{"header", {0, 0}},
			{"board", {0, 0}},
			{"text_area", {0, 0}},
			{"play_area", {0, 0}}
		};

		// ASCII members
		std::map<std::string, std::vector < std::string>> cribbage_boards;
		std::map<std::string, std::map<int, std::vector < std::string>>> cribbage_boards_coloured;
		std::vector<std::string> header;
		std::map<std::string, std::map<std::string, std::vector<std::string>>> ascii_deck;

};

#endif