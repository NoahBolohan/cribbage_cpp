#include "headers/CribbageFunctions.h"

int main() {

	initscr();
	int number_of_players = 3;

	Cribbage cribbage(number_of_players);
	cribbage.StartGame();

	getch();

	return 0;
}