#include <iostream>
#include <cstdlib>
#include "headers/CribbageFunctions.h"
#include "headers/DeckFunctions.h"
#include "headers/Functions.h"

int main() {
	int number_of_players = 2; //2 for now, 3 eventually

	Cribbage cribbage(number_of_players);

	std::cout << "Welcome to cribbage!" << std::endl;

	cribbage.Round();

	system("pause");

	return 0;
}