#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>


int part1(std::vector<int>& input) {
	int avg = 0;
	for (auto x : input) {
		avg += x;
	}
	int min_fuel = std::numeric_limits<int>::max();
	for (int i = 0; i <= avg+1; i++) {
		int fuel = 0;
		for (auto x : input) {
			fuel += std::abs(x - i);
		}
		min_fuel = std::min(min_fuel, fuel);
	}

	return min_fuel;
}

int part1_alt(std::vector<int>& input) {
	std::sort(input.begin(), input.end());
	int median = input[input.size() / 2];
	int fuel = 0;
	for (auto x : input) {
		fuel += std::abs(x - median);
	}
	return fuel;
}

int part2(std::vector<int>& input) {
	int avg = 0;
	for (auto x : input) {
		avg += x;
	}
	avg /= input.size();
	int min_fuel = std::numeric_limits<int>::max();;
	for (int i = 0; i <= avg+1; i++) {
		int fuel = 0;
		for (auto x : input) {
			int dist = std::abs(x - i);

			fuel += dist*(dist + 1) / 2;
		}
		min_fuel = std::min(min_fuel, fuel);
	}

	return min_fuel;
}

int part2_alt(std::vector<int>& input) {
	int mean = 0;
	for (auto x : input){
		mean += x;
	}
	mean /= input.size();
	int fuel = 0;
	for (auto x : input) {
		int dist = std::abs(x - mean);
		fuel += dist * (dist + 1) / 2;
	}
	return fuel;
}


int main() {
	std::ifstream ifs("input.txt");
	std::vector<int> input;
	{
		std::string tempStr;
		while (std::getline(ifs, tempStr, ',')) {
			input.push_back(stoi(tempStr));
		}
	}

	std::cout << "Part 1: " << part1_alt(input) << std::endl;
	std::cout << "Part 2: " << part2_alt(input) << std::endl;
	return 0;
}