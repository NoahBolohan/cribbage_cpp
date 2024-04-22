#include <string> // std::string
#include <vector> // std::vector

#include "../headers/CribbageFunctions.h"

void Cribbage::GenerateWelcomeText() {
	welcome_text = {
			"Welcome to Cribbage!",
			"",
			"Hit any key to start..."
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

	cribbage_boards_coloured.insert(
		{
			"3p_simple_hori",
			{
				{
					1,
					{
						"                                                          ",
						" ,    -- ----- ----- ----- ----- ----- ----- ----- -    , ",
						"                                                          ",
						"                                                          ",
						" |                                                       |",
						" |                                                        ",
						"                                                          ",
						" |       ----- ----- ----- ----- ----- ----- ----- -    ` ",
						" |                                                        ",
						"                                                          ",
						"                                                          ",
						" `    -- ----- ----- ----- ----- ----- ----- -----   ---  ",
						"                                                          ",
					}
				},
				{
					2,
					{
						"                                                          ",
						"                                                          ",
						"   ,  -- ----- ----- ----- ----- ----- ----- ----- -  ,   ",
						"                                                          ",
						"   |                                                   |  ",
						"   |                                                      ",
						"         ----- ----- ----- ----- ----- ----- ----- -  `   ",
						"   |                                                      ",
						"   |                                                      ",
						"                                                          ",
						"   `  -- ----- ----- ----- ----- ----- ----- -----   ---  ",
						"                                                          ",
						"                                                          "
					}
				},
				{
					3,
					{
						"                                                          ",
						"                                                          ",
						"                                                          ",
						"     ,-- ----- ----- ----- ----- ----- ----- ----- -,     ",
						"     |                                               |    ",
						"     |   ----- ----- ----- ----- ----- ----- ----- -`     ",
						"                                                          ",
						"     |                                                    ",
						"     |                                                    ",
						"     `-- ----- ----- ----- ----- ----- ----- -----   ---  ",
						"                                                          ",
						"                                                          ",
						"                                                          "
					}
				},
				{
					4,
					{
						"        45    50    55    60    65    70    75    80      ",
						" ,      |     |     |     |     |     |     |     |     , ",
						"   ,    |     |     |     |     |     |     |     |   ,   ",
						"     ,  |     |     |     |     |     |     |     | ,     ",
						"                                                          ",
						"        |     |     |     |     |     |     |     | `     ",
						"4- - - X|     |     |     |     |     |     |     |   `   ",
						"0       |     |     |     |     |     |     |     |     ` ",
						"        120   115   110   105   100   95    S     85      ",
						"     `  |     |     |     |     |     |     |     |:|   | ",
						"   `    |     |     |     |     |     |     |     |:|   | ",
						" `      |     |     |     |     |     |     |     |:|   | ",
						"         35    30    25    20    15    10    5            "
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

	cribbage_boards_coloured_routes.insert(
		{
			"3p_simple_hori",
			{
				{
					1,
					{
						{11,53},
						{11,49},{11,48},{11,47},{11,46},{11,45},
						{11,43},{11,42},{11,41},{11,40},{11,39},
						{11,37},{11,36},{11,35},{11,34},{11,33},
						{11,31},{11,30},{11,29},{11,28},{11,27},
						{11,25},{11,24},{11,23},{11,22},{11,21},
						{11,19},{11,18},{11,17},{11,16},{11,15},
						{11,13},{11,12},{11,11},{11,10},{11,9},
						{11,7},{11,6},{11,1},{8,1},{7,1},
						{5,1},{4,1},{1,1},{1,6},{1,7},
						{1,9},{1,10},{1,11},{1,12},{1,13},
						{1,15},{1,16},{1,17},{1,18},{1,19},
						{1,21},{1,22},{1,23},{1,24},{1,25},
						{1,27},{1,28},{1,29},{1,30},{1,31},
						{1,33},{1,34},{1,35},{1,36},{1,37},
						{1,39},{1,40},{1,41},{1,42},{1,43},
						{1,45},{1,46},{1,47},{1,48},{1,49},
						{1,51},{1,56},{4,57},{7,56},{7,51},
						{7,49},{7,48},{7,47},{7,46},{7,45},
						{7,43},{7,42},{7,41},{7,40},{7,39},
						{7,37},{7,36},{7,35},{7,34},{7,33},
						{7,31},{7,30},{7,29},{7,28},{7,27},
						{7,25},{7,24},{7,23},{7,22},{7,21},
						{7,19},{7,18},{7,17},{7,16},{7,15},
						{7,13},{7,12},{7,11},{7,10},{7,9},
						{6,7}
					}
				},
				{
					2,
					{
						{10,53},

						{10,49},{10,48},{10,47},{10,46},{10,45},
						{10,43},{10,42},{10,41},{10,40},{10,39},
						{10,37},{10,36},{10,35},{10,34},{10,33},
						{10,31},{10,30},{10,29},{10,28},{10,27},
						{10,25},{10,24},{10,23},{10,22},{10,21},
						{10,19},{10,18},{10,17},{10,16},{10,15},
						{10,13},{10,12},{10,11},{10,10},{10,9},
						{10,7},{10,6},{10,3},{8,3},{7,3},
						{5,3},{4,3},{2,3},{2,6},{2,7},
						{2,9},{2,10},{2,11},{2,12},{2,13},
						{2,15},{2,16},{2,17},{2,18},{2,19},
						{2,21},{2,22},{2,23},{2,24},{2,25},
						{2,27},{2,28},{2,29},{2,30},{2,31},
						{2,33},{2,34},{2,35},{2,36},{2,37},
						{2,39},{2,40},{2,41},{2,42},{2,43},
						{2,45},{2,46},{2,47},{2,48},{2,49},
						{2,51},{2,54},{4,55},{6,54},{6,51},
						{6,49},{6,48},{6,47},{6,46},{6,45},
						{6,43},{6,42},{6,41},{6,40},{6,39},
						{6,37},{6,36},{6,35},{6,34},{6,33},
						{6,31},{6,30},{6,29},{6,28},{6,27},
						{6,25},{6,24},{6,23},{6,22},{6,21},
						{6,19},{6,18},{6,17},{6,16},{6,15},
						{6,13},{6,12},{6,11},{6,10},{6,9},
						{6,7}
					}
				},
				{
					3,
					{
						{9,53},

						{9,49},{9,48},{9,47},{9,46},{9,45},
						{9,43},{9,42},{9,41},{9,40},{9,39},
						{9,37},{9,36},{9,35},{9,34},{9,33},
						{9,31},{9,30},{9,29},{9,28},{9,27},
						{9,25},{9,24},{9,23},{9,22},{9,21},
						{9,19},{9,18},{9,17},{9,16},{9,15},
						{9,13},{9,12},{9,11},{9,10},{9,9},
						{9,7},{9,6},{9,5},{8,5},{7,5},
						{5,5},{4,5},{3,5},{3,6},{3,7},
						{3,9},{3,10},{3,11},{3,12},{3,13},
						{3,15},{3,16},{3,17},{3,18},{3,19},
						{3,21},{3,22},{3,23},{3,24},{3,25},
						{3,27},{3,28},{3,29},{3,30},{3,31},
						{3,33},{3,34},{3,35},{3,36},{3,37},
						{3,39},{3,40},{3,41},{3,42},{3,43},
						{3,45},{3,46},{3,47},{3,48},{3,49},
						{3,51},{3,52},{4,53},{5,52},{5,51},
						{5,49},{5,48},{5,47},{5,46},{5,45},
						{5,43},{5,42},{5,41},{5,40},{5,39},
						{5,37},{5,36},{5,35},{5,34},{5,33},
						{5,31},{5,30},{5,29},{5,28},{5,27},
						{5,25},{5,24},{5,23},{5,22},{5,21},
						{5,19},{5,18},{5,17},{5,16},{5,15},
						{5,13},{5,12},{5,11},{5,10},{5,9},
						{6,7}
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

			if (value == "10") {

				std::string value_string1 = "|v  |";
				value_string1.at(1) = value[0];
				value_string1.at(2) = value[1];

				std::string value_string2 = "|  v|";
				value_string2.at(2) = value[0];
				value_string2.at(3) = value[1];

				ascii_cards["full"][value][suit] = {
					" --- ",
					value_string1,
					suit_string,
					value_string2,
					" --- "
				};

				value_string1 = "|v";
				value_string2 = "|v";
				suit_string = "|s";

				value_string1.at(1) = value[0];
				value_string2.at(1) = value[1];
				suit_string.at(1) = s;

				ascii_cards["partial"][value][suit] = {
				" -",
				value_string1,
				value_string2,
				suit_string,
				" -"
				};
			} 
			else {
				std::string value_string1 = "|v  |";
				value_string1.at(1) = value[0];

				std::string value_string2 = "|  v|";
				value_string2.at(3) = value[0];

				ascii_cards["full"][value][suit] = {
					" --- ",
					value_string1,
					suit_string,
					value_string2,
					" --- "
				};

				value_string1 = "|v";
				suit_string = "|s";

				value_string1.at(1) = value[0];
				suit_string.at(1) = s;

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
}

void Cribbage::GenerateCardAsciis() {

	card_back_vert = {
		" --- ",
		"|\\ /|",
		"| X |",
		"|/ \\|",
		" --- ",
	};

	card_back_hori = {
		" -  -  - ",
		"|   X   |",
		" -  -  - "
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