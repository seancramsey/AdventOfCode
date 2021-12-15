#include <iostream>
#include <fstream>
#include <string>
#include <vector>


struct Lanternfish {
	std::vector<int> internalTimer;

	void insert(int t) {
		internalTimer.push_back(t);
	}
	void create() {
		internalTimer.push_back(8);
	}
};

void parseInput(Lanternfish& fish) {
	std::ifstream ifs("input.txt");

	std::string numStr;
	while (std::getline(ifs, numStr, ',')) {
		fish.internalTimer.push_back(stoi(numStr));
	}
}
//brute force simulation is good enough for part 1
size_t part1(Lanternfish fish, int numDays = 80) {

	while (numDays--) {
		//simulate all fish
		size_t currentPopulation = fish.internalTimer.size();
		for (size_t i = 0; i < currentPopulation; i++) {
			if (fish.internalTimer[i] == 0) {
				//birth new fish
				fish.create();
				//reset timer
				fish.internalTimer[i] = 7;
			}
			fish.internalTimer[i]--;
		}
	}

	return fish.internalTimer.size();
}
//HOWEVER, we gotta get clever for part 2
uint64_t part2(Lanternfish fish, int numDays = 256) {
	std::vector<uint64_t> cycle(10, 0);
	for (int timerVal : fish.internalTimer) {
		cycle[timerVal + 1]++;
	}
	for (int i = 0; i < numDays; i++) {
		for (int j = 0; j <= 8; j++) {
			cycle[j] = cycle[j + 1];
		}
		cycle[9] = cycle[0];
		cycle[7] += cycle[0];
		cycle[0] = 0;
	}

	uint64_t totalFishPopulation = 0;

	for (uint64_t x : cycle) totalFishPopulation += x;

	return totalFishPopulation;
}

int main(int argv , char ** argc) {
	Lanternfish fish;
	parseInput(fish);
	std::cout << "Part 1: " << part1(fish) << std::endl;
	std::cout << "Part 2: " << part2(fish, atoi(argc[1])) << std::endl;
	return 0;
}