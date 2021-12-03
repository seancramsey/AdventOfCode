#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

int part1() {
	int x_pos = 0,
		y_pos = 0;

	std::ifstream ifs("input.txt");

	std::string command;
	int val;
	while (!ifs.eof()) {
		ifs >> command >> val;
		
		switch (command[0]) {
		case 'f': x_pos += val; break;
		case 'u': y_pos -= val; break;
		case 'd': y_pos += val; break;
		}
	}
	return x_pos * y_pos;
}

int part2() {
	int x_pos = 0,
		y_pos = 0,
		aim = 0;

	std::ifstream ifs("input.txt");

	std::string command;
	int val;
	while (!ifs.eof()) {
		ifs >> command >> val;

		switch (command[0]) {
		case 'f': 
			x_pos += val; 
			y_pos += (aim * val);
			break;
		case 'u': aim -= val; break;
		case 'd': aim += val; break;
		}
	}
	return x_pos * y_pos;
}

int main() {

	//std::cout << "Part 1: " << part1() << std::endl;
	std::cout << "Part 2: " << part2() << std::endl;
	return 0;
}