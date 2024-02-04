#include <iostream>
#include <cstdlib>
#include "CribbageFunctions.h"
#include "DeckFunctions.h"

int main() {
	Deck deck;
	int number_of_players = 2;

	Cribbage cribbage(number_of_players, deck);

	system("pause");

	return 0;
}