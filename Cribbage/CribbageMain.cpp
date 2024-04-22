#include "headers/CribbageFunctions.h"

int main() {
	//int number_of_players = 2;

	//Cribbage cribbage(
	//	number_of_players,
	//	"2p_simple_hori",
	//	{ 
	//		{"board", {13, 58, 0, 0}},
	//		{"text_area", {20, 51, 13, 0}},
	//		{"play_area", {22, 37, 0, 58}}
	//	}
	//);

	int number_of_players = 3;

	Cribbage cribbage(
		number_of_players,
		"3p_simple_hori",
		{
			{"board", {15, 61, 0, 0}},
			{"text_area", {20, 51, 15, 0}},
			{"play_area", {22, 37, 0, 61}}
		}
	);

	cribbage.StartGame();

	getch();

	return 0;
}