#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>

#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <functional>

void parseInput(std::vector<std::vector<std::string>>& full_signalPatterns, std::vector<std::vector<std::string>>& full_displays) {
	std::ifstream ifs("input.txt");
	std::string line;

	auto split = [](std::string line) {
		std::vector<std::string> res;
		int i = 0, j = 1;
		while (j <= line.size()) {
			if (j == line.size() || line[j] == ' ') {
				res.push_back(line.substr(i, j - i));
				while (j < line.size() && line[j] == ' ') {
					j++;
				}
				i = j;
			}
			j++;
		}
		return res;
	};
	while (std::getline(ifs, line)) {
		size_t lineBreak = line.find(" | ");
		std::string //
			sigp = line.substr(0, lineBreak),
			disp = line.substr(lineBreak + 3);
		full_signalPatterns.push_back(std::move(split(sigp)));
		full_displays.push_back(std::move(split(disp)));
	}
}


int part1(std::vector<std::vector<std::string>>& full_displays) {
	int count = 0;
	for (auto& display : full_displays) {
		for (auto& str : display) {
			size_t s = str.size();
			if (s == 2 || s == 4 || s == 3 || s == 7) {
				count++;
			}
		}
	}
	return count;
}

std::bitset<7> makeBitSet(std::string& str) {
	std::bitset<7> b_set;
	for (auto c : str) {
		b_set.set(c - 'a');
	}
	return b_set;
}
int solve(std::vector<std::string>& signalPatterns, std::vector<std::string>& displays) {
	std::vector<std::bitset<7>> bits(10);
	std::unordered_map<std::bitset<7>, int> mapping;
	std::unordered_set<std::bitset<7>> unknown;

	for (auto& str : signalPatterns) {
		if (str.size() == 2) {
			bits[1] = makeBitSet(str);
			mapping[bits[1]] = 1;
		}
		else if (str.size() == 4) {
			bits[4] = makeBitSet(str);
			mapping[bits[4]] = 4;
		}
		else if (str.size() == 3) {
			bits[7] = makeBitSet(str);
			mapping[bits[7]] = 7;
		}
		else if (str.size() == 7) {
			bits[8] = makeBitSet(str);
			mapping[bits[8]] = 8;
		}
		else
			unknown.insert(makeBitSet(str));
	}
	//begin process of elimination
	std::bitset<7> mask;
	//6
	mask = bits[1] ^ bits[8];
	for (auto& pattern : unknown) {
		if ((pattern & mask) == mask) {
			bits[6] = pattern;
			mapping[pattern] = 6;
			break;
		}
	}
	unknown.erase(bits[6]);
	//9
	mask = bits[4];
	for (auto& pattern : unknown) {
		if ((pattern & mask) == mask) {
			//std::cout << "found 9\n";
			bits[9] = pattern;
			mapping[pattern] = 9;
			break;
		}
	}
	unknown.erase(bits[9]);
	//3
	mask = bits[1];
	for (auto& pattern : unknown) {
		if ((pattern & mask) == mask && pattern.count() == 5) {
			//std::cout << "found 3\n";
			bits[3] = pattern;
			mapping[pattern] = 3;
			break;
		}
	}
	unknown.erase(bits[3]);
	//0
	mask = bits[1] | ~bits[3];
	for (auto& pattern : unknown) {
		if ((pattern & mask) == mask) {
			//std::cout << "found 0\n";
			bits[0] = pattern;
			mapping[pattern] = 0;
			break;
		}
	}
	unknown.erase(bits[0]);
	//5
	mask = bits[9];
	for (auto& pattern : unknown) {
		if ((pattern & mask) == pattern) {
			//std::cout << "found 5\n";
			bits[5] = pattern;
			mapping[pattern] = 5;
			break;
		}
	}
	unknown.erase(bits[5]);
	//2
	bits[2] = *unknown.begin();
	mapping[bits[2]] = 2;
	
	int number = 0;
	for (auto& disp : displays) {
		number *= 10;
		number += mapping[makeBitSet(disp)];
	}
	return number;
}

int part2(std::vector<std::vector<std::string>>& full_signalPatterns, std::vector<std::vector<std::string>>& full_displays) {
	int answer = 0;
	for (int i = 0; i < full_signalPatterns.size() ; i++) {
		answer += solve(full_signalPatterns[i], full_displays[i]);
	}
	return answer;
}
int main() {
	std::vector<std::vector<std::string>>
		full_signalPatterns,
		full_displays;
	parseInput(full_signalPatterns, full_displays);
	/*
	for (int i = 0; i < signalPatterns.size(); i++) {
		for (std::string& str : signalPatterns[i])
			std::cout << str << ' ';
		std::cout << "| ";
		for (std::string& str : displays[i])
			std::cout << str << ' ';
		std::cout << '\n';
	}*/
	std::cout << "Part 1: " << part1(full_displays) << std::endl;
	std::cout << "Part 2: " << part2(full_signalPatterns, full_displays) << std::endl;
}

/*/NOTES:
0 = 6
1 = 2
2 = 5
3 = 5
4 = 4
5 = 5
6 = 6
7 = 3
8 = 7
9 = 6

*/