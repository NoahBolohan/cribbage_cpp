#include <string>
#include <vector>

class Cribbage {
	public:
		Cribbage(int, Deck);

		void Deal();
		void PassToCrib(std::string, std::string);
		void DrawStarter();
		void ThePlay(int);
		void TheGo();
		void Pegging();

	private:
		int number_of_players;

		Deck deck;
		std::vector<int> scores;
		std::vector<std::vector<std::string>> hands;
		std::vector<std::string> crib;
		std::string starter;

		const int score_target = 121;

		int pegging_total = 0;
		int dealer = 0;

};