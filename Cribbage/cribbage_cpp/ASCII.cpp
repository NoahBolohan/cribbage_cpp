#include <string> // std::string
#include <vector> // std::vector

#include "../headers/CribbageFunctions.h"

void Cribbage::GenerateHeader() {
	header = {
			"Welcome to Cribbage!",
			"",
			"Rules:",
			"------",
			"1. Have fun!"
	};
}

void Cribbage::GenerateBoard() {

	cribbage_boards.insert(
		{
			"3p_std_vert",
			{
				"       /-----------------------------\\       ",
				"      /       o     o | o     o       \\      ",
				"     /    /-----------4-----------\\    \\     ",
				"    / o  /     o    o | o    o     \\  o \\    ",
				"   /    /    /--------0--------\\    \\    \\   ",
				"  /    / o  /   o   o | o   o   \\  o \\    \\  ",
				" /    /    /   /-------------\\   \\    \\    \\ ",
				"/    /    / o /      END      \\ o \\    \\    \\",
				"| o /    /   /        _        \\   \\    \\ o |",
				"|   | o /   /        / \\        \\   \\ o |   |",
				"|   |   | o |       | o |       | o |   |   |",
				"|   |   |   |        \\_/        |   |   |   |",
				"| o | o | o |         |         | o | o | o |",
				"|---|3 5|---|   |---|120|---|   |---|4 5|---|",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o | ",
				"|---|3 0|---|   |---|115|---|   |---|5 0|---|",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o | ",
				"|---|2 5|---|   |---|110|---|   |---|5 5|---|",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o | ",
				"|---|2 0|---|   |---|105|---|   |---|6 0|---|",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o | ",
				"|---|1 5|---|   |---|100|---|   |---|6 5|---|",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o | ",
				"|---|1 0|---|   |---|9 5|---|   |---|7 0|---|",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o | ",
				"|---| 5 |---|   |---|SSS|---|   |---|7 5|---|",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"| o | o | o |   | o | o | o |   | o | o | o |",
				"|---|---|---|   |---|8 5|---|   |---|8 0|---|",
				"    Start       | o | o | o |   | o | o | o |",
				"|---|---|---|   |   |   \\ o \\---/ o /   |   |",
				"| o | o | o |   |   \\    \\    o    /    /   |",
				"|---|---|---|   \\    \\ o  \\-------/  o /    /",
				"| o | o | o |    \\    \\       o       /    / ",
				"|---|---|---|     \\ o  \\-------------/  o /  ",
				"| o | o | o |      \\          o          /   ",
				"|---|---|---|       \\-------------------/    "
			}
		}
	);

	cribbage_boards.insert(
		{
			"3p_std_hori",
			{
				"                        45          50          55          60          65          70          75          80               ",
				"      /-----------------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|--------\\       ",
				"     /            o    o| o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | o o o o o |o        \\      ",
				"    /  o  /-------------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|------\\   \\     ",
				"   /     /         o   o| o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | o o o o o |o      \\ o \\    ",
				"  /     /  o /----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|----\\ o \\   \\   ",
				" /     /    /       o  o| o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | o o o o o |o  o \\   \\   \\  ",
				" | o  /    /   o /------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|--\\   \\   \\   \\ ",
				" |   | o  /    /                                                                                                | o | o | o |",
				" |   |   | o  /         |-----------|-----------|-----------|-----------|-----------|-----------|-----------|--/   /   /   / ",
				" |   |   |   |          | o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | o o o o o |o  o /   /   /  ",
				" | o | o | o | E  / \\   |-----------|-----------|-----------|-----------|-----------|-----------|-----------|----/ o /   /   ",
				"4|-----------| N | o |--| o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | o o o o o |o      / o /    ",
				"0| o | o | o | D  \\ /   |-----------|-----------|-----------|-----------|-----------|-----------|-----------|------/   /     ",
				" |   |   |   |          | o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | o o o o o |o        /      ",
				" |   |   | o  \\         |-----------|-----------|-----------|-----------|-----------|-----------|-----------|--------/       ",
				" |   | o  \\    \\        120         115         110         105         100         95          S           85               ",
				" | o  \\    \\   o \\------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|   |-----------|",
				" \\     \\    \\       o  o| o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | S | o | o | o |",
				"  \\     \\  o \\----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------| T |-----------|",
				"   \\     \\         o   o| o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | A | o | o | o |",
				"    \\  o  \\-------------|-----------|-----------|-----------|-----------|-----------|-----------|-----------| R |-----------|",
				"     \\            o    o| o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | o o o o o | T | o | o | o |",
				"      \\-----------------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|   |-----------|",
				"                        35          30          25          20          15          10          5                            "
			}
		}
	);

	cribbage_boards.insert(
		{
			"3p_simple_hori",
			{
				"        45    50    55    60    65    70    75    80      ",
				" ,    --|-----|-----|-----|-----|-----|-----|-----|-    , ",
				"   ,  --|-----|-----|-----|-----|-----|-----|-----|-  ,   ",
				"     ,--|-----|-----|-----|-----|-----|-----|-----|-,     ",
				" | | |                                               | | |",
				" | | |  |-----|-----|-----|-----|-----|-----|-----|-`     ",
				"4- - - X|-----|-----|-----|-----|-----|-----|-----|-  `   ",
				"0| | |  |-----|-----|-----|-----|-----|-----|-----|-    ` ",
				" | | |  120   115   110   105   100   95    S     85      ",
				"     `--|-----|-----|-----|-----|-----|-----|-----|:|---| ",
				"   `  --|-----|-----|-----|-----|-----|-----|-----|:|---| ",
				" `    --|-----|-----|-----|-----|-----|-----|-----|:|---| ",
				"         35    30    25    20    15    10    5            "
			}
		}
	);

	cribbage_boards.insert(
		{
			"2p_simple_hori",
			{
				"      45    50    55    60    65    70    75    80     ",
				" ,  --|-----|-----|-----|-----|-----|-----|-----|-  ,  ",
				"   ,--|-----|-----|-----|-----|-----|-----|-----|-,    ",
				" | |                                               | | ",
				" | |  |-----|-----|-----|-----|-----|-----|-----|-`    ",
				"4- - X|-----|-----|-----|-----|-----|-----|-----|-  `  ",
				"0| |  120   115   110   105   100   95    S     85     ",
				" | |                                                   ",
				"   `--|-----|-----|-----|-----|-----|-----|-----|:|---|",
				" `  --|-----|-----|-----|-----|-----|-----|-----|:|---|",
				"     35    30    25    20    15    10    5             "
			}
		}
	);

	cribbage_boards_coloured.insert(
		{
			"2p_simple_hori",
			{
				{
					1,
					{
						"                                                       ",
						" ,  -- ----- ----- ----- ----- ----- ----- ----- -  ,  ",
						"                                                       ",
						" |                                                   | ",
						" |                                                     ",
						"       ----- ----- ----- ----- ----- ----- ----- -  `  ",
						" |                                                     ",
						" |                                                     ",
						"                                                       ",
						" `  -- ----- ----- ----- ----- ----- ----- -----   --- ",
						"                                                       "
					}
				},
				{
					2,
					{
						"                                                       ",
						"                                                       ",
						"   ,-- ----- ----- ----- ----- ----- ----- ----- -,    ",
						"   |                                               |   ",
						"   |   ----- ----- ----- ----- ----- ----- ----- -`    ",
						"                                                       ",
						"   |                                                   ",
						"   |                                                   ",
						"   `-- ----- ----- ----- ----- ----- ----- -----   --- ",
						"                                                       ",
						"                                                       ",
					}
				},
				{
					4,
					{
						"      45    50    55    60    65    70    75    80     ",
						"      |     |     |     |     |     |     |     |      ",
						"      |     |     |     |     |     |     |     |      ",
						"                                                       ",
						"      |     |     |     |     |     |     |     |      ",
						"4- - X|     |     |     |     |     |     |     |      ",
						"0     120   115   110   105   100   95    S     85     ",
						"                                                       ",
						"      |     |     |     |     |     |     |     |:|   |",
						"      |     |     |     |     |     |     |     |:|   |",
						"     35    30    25    20    15    10    5             "
					}
				}
			}
		}
	);

	cribbage_boards_coloured_routes.insert(
		{
			"2p_simple_hori",
			{
				{
					1,
					{
						{9,51},
						{9,47},{9,46},{9,45},{9,44},{9,43},
						{9,41},{9,40},{9,39},{9,38},{9,37},
						{9,35},{9,34},{9,33},{9,32},{9,31},
						{9,29},{9,28},{9,27},{9,26},{9,25},
						{9,23},{9,22},{9,21},{9,20},{9,19},
						{9,17},{9,16},{9,15},{9,14},{9,13},
						{9,11},{9,10},{9,9},{9,8},{9,7},
						{9,5},{9,4},{9,1},{7,1},{6,1},
						{4,1},{3,1},{1,1},{1,4},{1,5},
						{1,7},{1,8},{1,9},{1,10},{1,11},
						{1,13},{1,14},{1,15},{1,16},{1,17},
						{1,19},{1,20},{1,21},{1,22},{1,23},
						{1,25},{1,26},{1,27},{1,28},{1,29},
						{1,31},{1,32},{1,33},{1,34},{1,35},
						{1,37},{1,38},{1,39},{1,40},{1,41},
						{1,43},{1,44},{1,45},{1,46},{1,47},
						{1,49},{1,52},{3,53},{5,52},{5,49},
						{5,47},{5,46},{5,45},{5,44},{5,43},
						{5,41},{5,40},{5,39},{5,38},{5,37},
						{5,35},{5,34},{5,33},{5,32},{5,31},
						{5,29},{5,28},{5,27},{5,26},{5,25},
						{5,23},{5,22},{5,21},{5,20},{5,19},
						{5,17},{5,16},{5,15},{5,14},{5,13},
						{5,11},{5,10},{5,9},{5,8},{5,7},
						{5,5}
					}
				},
				{
					2,
					{
						{8,51},
						{8,47},{8,46},{8,45},{8,44},{8,43},
						{8,41},{8,40},{8,39},{8,38},{8,37},
						{8,35},{8,34},{8,33},{8,32},{8,31},
						{8,29},{8,28},{8,27},{8,26},{8,25},
						{8,23},{8,22},{8,21},{8,20},{8,19},
						{8,17},{8,16},{8,15},{8,14},{8,13},
						{8,11},{8,10},{8,9},{8,8},{8,7},
						{8,5},{8,4},{8,3},{7,3},{6,3},
						{4,3},{3,3},{2,3},{2,4},{2,5},
						{2,7},{2,8},{2,9},{2,10},{2,11},
						{2,13},{2,14},{2,15},{2,16},{2,17},
						{2,19},{2,20},{2,21},{2,22},{2,23},
						{2,25},{2,26},{2,27},{2,28},{2,29},
						{2,31},{2,32},{2,33},{2,34},{2,35},
						{2,37},{2,38},{2,39},{2,40},{2,41},
						{2,43},{2,44},{2,45},{2,46},{2,47},
						{2,49},{2,50},{3,51},{4,50},{4,49},
						{4,47},{4,46},{4,45},{4,44},{4,43},
						{4,41},{4,40},{4,39},{4,38},{4,37},
						{4,35},{4,34},{4,33},{4,32},{4,31},
						{4,29},{4,28},{4,27},{4,26},{4,25},
						{4,23},{4,22},{4,21},{4,20},{4,19},
						{4,17},{4,16},{4,15},{4,14},{4,13},
						{4,11},{4,10},{4,9},{4,8},{4,7},
						{5,5}
					}
				},
			}
		}
	);
}

void Cribbage::GenerateDeck() {

	ascii_cards["full"] = {};
	ascii_cards["partial"] = {};

	std::vector<std::string> card_values = { "Ace","2","3","4","5","6","7","8","9","10","Jack","Queen","King" };
	std::vector<std::string> card_suits = { "Hearts","Diamonds","Clubs","Spades" };

	for (auto value : card_values) {

		ascii_cards["full"][value] = {};
		ascii_cards["partial"][value] = {};

		for (auto suit : card_suits) {

			char v = value[0];

			std::string value_string1 = "|v  |";
			value_string1.at(1) = v;
			
			std::string value_string2 = "|  v|";
			value_string2.at(3) = v;

			char s;

			if (suit == "Hearts") {
				s = 'h';
			}

			if (suit == "Diamonds") {
				s = 'd';
			}
			if (suit == "Clubs") {
				s = 'c';
			}

			if (suit == "Spades") {
				s = 's';
			}

			std::string suit_string = "| s |";
			suit_string.at(2) = s;

			ascii_cards["full"][value][suit] = {
				" --- ",
				value_string1,
				suit_string,
				value_string2,
				" --- "
			};

			value_string1 = "|v";
			suit_string = "|s";

			value_string1.at(1) = v;
			suit_string.at(1) = v=s;

			ascii_cards["partial"][value][suit] = {
				" -",
				value_string1,
				suit_string,
				"| ",
				" -"
			};
		}
	}
}

void Cribbage::GenerateCardAsciis() {

	card_back = {
		" --- ",
		"|\\ /|",
		"| X |",
		"|/ \\|",
		" --- ",
	};

	ascii_deck_face_down = {
		"  --- ",
		"/|\\ /|",
		"|| X |",
		"||/ \\|",
		"|/---/",
		" ---  ",
	};
}

std::vector<std::string> Cribbage::GenerateAsciiDeckFaceUp(std::vector < std::string> card) {
	std::vector <std::string> ascii_card = ascii_cards["full"][card.at(0)][card.at(1)];

	return {
		" " + ascii_card.at(0),
		"/" + ascii_card.at(1),
		"|" + ascii_card.at(2),
		"|" + ascii_card.at(3),
		"|/---/",
		" ---  "
	};
}