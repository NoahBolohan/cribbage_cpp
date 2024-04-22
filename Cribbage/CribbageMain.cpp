#include "headers/CribbageFunctions.h"

int main() {
	int number_of_players = 2; //2 for now, 3 eventually

	Cribbage cribbage(
		number_of_players,
		"2p_simple_hori",
		{ 
			{"board", {13, 58, 0, 0}},
			{"text_area", {20, 51, 13, 0}},
			{"play_area", {22, 37, 0, 58}}
		}
	);

	cribbage.StartGame();

	getch();

	return 0;
}