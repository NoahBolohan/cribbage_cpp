#include <iostream>
#include <cstdlib>
#include "CribbageFunctions.h"
#include "DeckFunctions.h"

int main() {
	Deck deck;
	
	std::cout << deck.DrawCard() << std::endl;

	system("pause");

	return 0;
}