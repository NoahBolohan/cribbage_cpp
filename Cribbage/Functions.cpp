#include <vector>

#include "Functions.h"

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