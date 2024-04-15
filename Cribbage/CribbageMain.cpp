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
			{"board", {15, 61, 0, 0}},
			{"header", {10, 61, 15, 0}} 
		}
	);

	cribbage.StartGame();

	return 0;
}