#include <iostream>
#include <cstdlib>
#include "CribbageFunctions.h"
#include "DeckFunctions.h"

int main() {
	int number_of_players = 2; //2 or 3

	Cribbage cribbage(number_of_players);

	std::cout << "Welcome to cribbage!" << std::endl;

	cribbage.Round();

	system("pause");

	return 0;
}