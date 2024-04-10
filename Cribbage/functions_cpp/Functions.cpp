#include <vector>

#include "../headers/Functions.h"

std::vector<std::vector<int>> ComputeSubsets(int a, int b) {

	std::vector<std::vector<int>> subsets = { {} };

	int inc = 0;

	while (inc < (b - a)) {

		int subsets_size = subsets.size();
		for (int subset_index = 0; subset_index < subsets_size; subset_index++) {

			std::vector<int> subset = subsets.at(subset_index);
			subset.push_back(a + inc);

			subsets.push_back(subset);
		}
		inc++;
	}

	return subsets;
}

std::vector<std::vector<int>> ComputeSubsets(int a, int b, int n) {

	std::vector<std::vector<int>> subsets = { {} };
	std::vector<std::vector<int>> subsets_to_return;

	int inc = 0;

	while (inc < (b - a)) {

		int subsets_size = subsets.size();
		for (int subset_index = 0; subset_index < subsets_size; subset_index++) {

			std::vector<int> subset = subsets.at(subset_index);
			subset.push_back(a + inc);

			subsets.push_back(subset);
		}
		inc++;
	}

	for (auto &subset : subsets) {
		if (subset.size() == n) {
			subsets_to_return.push_back(subset);
		}
	}

	return subsets_to_return;
}