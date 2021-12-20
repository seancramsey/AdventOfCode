#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

//GLOBAL STUFF/////////////////////
struct pair_hash
{
	template <class T1, class T2>
	std::size_t operator() (const std::pair<T1, T2>& pair) const {
		return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
	}
};
std::unordered_map<std::pair<int, int>, char, pair_hash> image;
std::string lookup512;

int min_x = 0, max_x = 0, min_y = 0, max_y = 0;

bool flip = false;
///////////////////////////////////



void print() {
	std::vector<std::vector<char>> grid(max_y - min_y + 1, std::vector<char>(max_x - min_x + 1));

	std::cout << '\n';
	for (auto& [yx, v] : image) {
		int y = yx.first - min_y;
		if (y < 0 || y >= grid.size()) continue;
		int x = yx.second - min_x;
		if (x < 0 || x >= grid[y].size()) continue;

		grid[y][x] = v;
	}
	for (auto& row : grid) {
		for (auto ch : row) {
			std::cout << ch;
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

int main() {
	std::ifstream ifs("input.txt");
	std::getline(ifs, lookup512);
	std::string line;
	std::getline(ifs, line);
	size_t lineNum = -1;
	while (std::getline(ifs, line)) {
		lineNum++;
		for (size_t i = 0; i < line.size(); i++) {
			image[{lineNum, i}] = line[i];
		}
	}

	max_x = line.size()-1;
	max_y = lineNum;

	//add border, representing infitite background
	for (int y = min_y-1; y <= max_y+1; y++) {
		image[std::make_pair(y, min_x-1)] = '.';
		image[std::make_pair(y, max_x+1)] = '.';
	}
	for (int x = min_x-1; x <= max_x+1; x++) {
		image[std::make_pair(min_y-1, x)] = '.';
		image[std::make_pair(max_y+1, x)] = '.';
	}

	//std::cout << lookup512;
	//print();

	std::unordered_map<char, size_t> bg_Id{
		{'#', 511},
		{'.', 0}
	};
	//part1
	for (int step = 0; step < 50; step++) {
		//expand image boundary
		min_x--;
		min_y--;
		max_x++;
		max_y++;
		char old_bgCol = image[std::make_pair(min_y, min_x)];
		char new_bgCol = lookup512[bg_Id[old_bgCol]];
		//new image will store transformed image
		std::unordered_map<std::pair<int, int>, char, pair_hash> newImage;
		

		for (auto& [yx, _] : image) {

			std::string value = "";

			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					std::pair<int, int> c{ yx.first + i, yx.second + j };

					if (image.find(c) == image.end()) 
					{
						//EXTENDS BACKGROUND
						newImage[c] = new_bgCol;
						value.append(old_bgCol == '#' ? "1" : "0");
					}
					else
					{
						value.append((image[c] == '#' ? "1" : "0"));
					}
				}
			}
			newImage[yx] = lookup512[stoi(value, nullptr, 2)];
		}
		image = std::move(newImage);
		//print();
	}

	size_t count = 0;
	for (auto& [xy, v] : image) {
		count += (v == '#');
	}
	std::cout << "Part 1: " << count << std::endl;
}