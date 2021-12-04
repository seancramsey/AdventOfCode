#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

//PART 1
std::bitset<12> makeBitSet(std::vector<int>& counts) {
	std::string bitString(counts.size(), '0');
	for (int i = 0; i < 12; i++) {
		bitString[i] = counts[i] > 0 ? '1' : '0';
	}
	return std::bitset<12>(bitString);
}
int part1() {
	std::ifstream ifs("input.txt");
	std::vector<int> counts(12,0);
	std::string binaryNumber;
	while (!ifs.eof()) {
		ifs >> binaryNumber;
		for (int i = 0; i < 12; i++) {
			counts[i] += binaryNumber[i] == '1' ? 1 : -1;
		}
	}

	std::bitset<12> gamma = makeBitSet(counts);
	std::bitset<12> epsilon = ~gamma;

	return static_cast<int>(gamma.to_ulong() * epsilon.to_ulong());
}
//PART 1 END

//PART 2
#include <unordered_set>
#include <thread>
#include <iterator>
void eliminationProcedure(std::unordered_set<std::string>& process_set, char rule) {
	//while we can eliminate binary strings
	for (int i = 0; i < 12 && process_set.size() > 1; i++) {
		//first pass: get count of 1s vs 0s;
		int counter = 0;
		for (const std::string& str : process_set) {
			counter += str[i] == '1' ? 1 : -1;
		}
		//second pass: eliminate values that don't meet criteria
		char target;
		if(rule == '1')
			target = counter > 0 ? '1' : (counter < 0 ? '0' : '1');
		else if (rule == '0') {
			target = counter > 0 ? '0' : (counter < 0 ? '1' : '0');
		}
		std::unordered_set<std::string> eliminationSet;
		for (const std::string& str : process_set) {
			if (str[i] != target) {
				eliminationSet.insert(str);
			}
		}
		for (const std::string& str : eliminationSet) {
			process_set.erase(str);
		}
	}
}
int part2() {
	std::ifstream ifs("input.txt");
	std::unordered_set<std::string> set_oxyGenerator;
	std::copy(std::istream_iterator<std::string>(ifs), 
		std::istream_iterator<std::string>(), 
		std::inserter(set_oxyGenerator, set_oxyGenerator.end()));

	std::unordered_set<std::string> set_co2Scrubber(set_oxyGenerator.begin(), set_oxyGenerator.end());

	std::thread th1(eliminationProcedure, std::ref(set_oxyGenerator), '1');
	std::thread th2(eliminationProcedure, std::ref(set_co2Scrubber), '0');

	th1.join();
	th2.join();

	std::string o2 = *set_oxyGenerator.begin();
	std::string co2 = *set_co2Scrubber.begin();

	return static_cast<int>(std::bitset<12>(o2).to_ulong() * std::bitset<12>(co2).to_ulong());
}
//PART 2 END

int main() {
	std::cout << "Part 1: " << part1() << std::endl;
	std::cout << "Part 2: " << part2() << std::endl;
	return 0;
}