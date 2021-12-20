#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

//GLOBAL STUFF/////////////////////
std::unordered_map<int, std::unordered_map<int, char>> image;
std::string lookup512;

int min_x = 0, max_x = 0, min_y = 0, max_y = 0;

bool flip = false;
///////////////////////////////////



void print() {
	std::vector<std::vector<char>> grid(max_y - min_y + 1, std::vector<char>(max_x - min_x + 1));

	std::cout << '\n';

	for (int y = min_y; y <= max_y; y++) {
		for (int x = min_x; x <= max_x; x++) {
			int y_ = y - min_y;
			int x_ = x - min_x;
			grid[y_][x_] = image[y][x];
		}
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

			image[lineNum][i] = line[i];
		}
	}

	max_x = line.size()-1;
	max_y = lineNum;

	//add border, representing infitite background
	for (int y = min_y-1; y <= max_y+1; y++) {
		image[y][min_x - 1] = '.';
		image[y][max_x + 1] = '.';
	}
	for (int x = min_x-1; x <= max_x+1; x++) {
		image[min_y - 1][x] = '.';
		image[max_y + 1][x] = '.';
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
		char old_bgCol = image[min_y][min_x];
		char new_bgCol = lookup512[bg_Id[old_bgCol]];
		//new image will store transformed image
		std::unordered_map<int, std::unordered_map<int, char>> newImage;
		
		for (int y = min_y; y <= max_y; y++) {
			for (int x = min_x; x <= max_x; x++) {

				std::string value = "";

				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						if (image.find(y+i) == image.end() || image[y+i].find(x+j) == image[y+i].end())
						{
							//EXTENDS BACKGROUND
							newImage[y+i][x+j] = new_bgCol;
							value.append(old_bgCol == '#' ? "1" : "0");
						}
						else
						{
							value.append((image[y+i][x+j] == '#' ? "1" : "0"));
						}
					}
				}
				newImage[y][x] = lookup512[stoi(value, nullptr, 2)];
			}
		}
		image = std::move(newImage);
		//print();
	}

	size_t count = 0;
	for (int y = min_y; y <= max_y; y++) {
		for (int x = min_x; x <= max_x; x++) {
			count += image[y][x] == '#';
		}
	}
	std::cout << "Part 1: " << count << std::endl;
}