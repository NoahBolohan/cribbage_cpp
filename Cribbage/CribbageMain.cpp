#include <iostream>
#include <cstdlib>
#include "headers/CribbageFunctions.h"
#include "headers/DeckFunctions.h"
#include "headers/Functions.h"
#include "headers/Windows.h"

int main() {
	int number_of_players = 2; //2 for now, 3 eventually

	Cribbage cribbage(
		number_of_players,
		{ 
			{"board", {13, 57, 0, 0}},
			{"header", {7, 32, 0, 57}},
			{"text_area", {7, 57, 13, 0}},
			{"play_area", {13, 32, 7, 57}}
		}
	);

	cribbage.StartGame();

	return 0;
}