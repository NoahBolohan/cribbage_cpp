#include <string> // std::string
#include <vector> // std::vector

#include "../headers/DeckFunctions.h"

int Deck::GetNumberOfPlayers() { return number_of_players; }

int Deck::GetDealerIndex() { return dealer_index; }

int Deck::GetCurrentPlayerIndex() { return current_player_index; }

std::vector<std::vector<std::vector<std::string>>> Deck::GetHands() { return hands; }

std::vector<std::map<std::string, std::vector<std::vector<std::string>>>> Deck::GetSidePiles() { return side_piles; }

std::map<std::string, std::vector<std::vector<std::string>>> Deck::GetCommonPiles() { return common_piles; }