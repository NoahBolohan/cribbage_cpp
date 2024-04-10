#include <iostream> // std::cout, std::cin
#include <string> // std::string
#include <vector> // std::vector
#include <ctime> // std::time 
#include <cstdlib> // std::rand, std::srand
#include <algorithm> // std::max. std::min, std::remove

#include "CribbageFunctions.h"
#include "DeckFunctions.h"
#include "Functions.h"

bool Cribbage::CheckFlush(std::vector<std::vector<std::string>> cards_to_check, int n_points, std::string announcement) {

	std::vector<std::string> suits;
	bool return_value = false;

	for (auto card : cards_to_check) {
		suits.push_back(card.at(1));
	}

	if (std::adjacent_find(
		suits.begin(),
		suits.end(),
		std::not_equal_to<>()
	) == suits.end()) {

		AddPoints(deck.GetCurrentPlayerIndex(), n_points, announcement);
		return_value = true;
	}

	return return_value;
}

bool Cribbage::CheckPairs(std::vector<std::vector<std::string>> cards_to_check, int n_points, std::string announcement) {

	std::vector<std::string> values;
	bool return_value = false;

	for (auto card : cards_to_check) {
		values.push_back(card.at(0));
	}

	if (std::adjacent_find(
		values.begin(),
		values.end(),
		std::not_equal_to<>()
	) == values.end()) {

		AddPoints(deck.GetCurrentPlayerIndex(), n_points, announcement);
		return_value = true;
	}

	return return_value;
}

bool Cribbage::CheckRuns(std::vector<std::vector<std::string>> cards_to_check, int n_points, std::string announcement) {

	std::vector<std::string> values;
	bool return_value = false;

	for (auto card : cards_to_check) {
		values.push_back(card.at(0));
	}

	std::vector<int> values_indices;
	std::vector<int> range_indices;

	for (auto value : values) {
		values_indices.push_back(run_ordering[value]);
		if (value == "Ace") {
			values_indices.push_back(13);
		}
	}

	std::sort(values_indices.begin(), values_indices.end());

	for (int i = values_indices.at(0); i <= values_indices.back(); i++) {
		range_indices.push_back(i);
	}

	if (values_indices == range_indices) {

		AddPoints(deck.GetCurrentPlayerIndex(), n_points, announcement);
		return_value = true;
	}

	return return_value;
}

void Cribbage::CheckRunsForShow(std::vector<std::vector<std::string>> cards) {}

void Cribbage::CheckPairsForShow(std::vector<std::vector<std::string>> cards) {

	std::map<std::string, int> value_counter;

	for (auto card : cards) {
		if (value_counter.find(card.at(0)) == value_counter.end()) {
			value_counter[card.at(0)] = 1;
		}
		else {
			value_counter[card.at(0)] += 1;
		}
	}

	for (auto const& item : value_counter) {
		if (item.second == 2) {
			AddPoints(deck.GetCurrentPlayerIndex(), 2, "That's a pair");
		}
		else if (item.second == 3) {
			AddPoints(deck.GetCurrentPlayerIndex(), 3, "Nice triple");
		}
		else if (item.second == 4) {
			AddPoints(deck.GetCurrentPlayerIndex(), 4, "Four-of-a-kind");
		}
	}
}

void Cribbage::CheckFlushForShow(std::vector<std::vector<std::string>> cards) {}