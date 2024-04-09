#ifndef CRIBBAGE_HEADER
#define CRIBBAGE_HEADER

#include <string>
#include <vector>
#include <map>
#include "DeckFunctions.h"

class Cribbage {
	public:
		Cribbage(int);

		void InitializeScores();
		void InitializePiles();
		void Deal();
		void PassToCrib(std::vector<std::vector<std::string>>);
		void DrawStarter();
		void AnnouncePoints(int, std::string);
		void ThePlayPoints();
		bool CheckPairsForLength(int, int, std::string);
		bool CheckRunsForLength(int, int, std::string);
		void GoPoints();
		void ThePlay();
		void UpTo31();
		void RemovePlayerFromThePlay(int);
		void RemovePlayerFrom31(int);
		void TheShow();
		void TheShowPoints(int, std::vector<std::vector<std::string>>);
		void AddPoints(int, int, std::string);
		void DisplayScore();

		void Round();

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
};

#endif