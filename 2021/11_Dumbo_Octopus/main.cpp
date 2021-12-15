#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

std::vector<std::string> parseInput() {
	std::ifstream ifs("input.txt");

	std::vector<std::string> res;
	std::copy(std::istream_iterator<std::string>(ifs), std::istream_iterator<std::string>(), std::back_inserter(res));
	return res;
}
uint32_t flash(std::vector<std::string>& grid, int i, int j) {
	grid[i][j] = '9' - 18;
	uint32_t flashes = 1;
	for (int ii = i-1; ii <= i+1; ii++) {
		for (int jj = j-1; jj <= j+1; jj++) {
			//if valid cell, increment. flash it if need be
			if (0 <= ii && ii < grid.size() && 0 <= jj && jj < grid[i].size() && grid[ii][jj] >= '0' && ++grid[ii][jj] > '9')
				flashes += flash(grid, ii, jj);
		}
	}
	return flashes;
}

uint32_t simulation_step(std::vector<std::string>& grid) {
	int flashes = 0;
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			//step 1, increment
			grid[i][j]++;
			//step 2, if cell > 9 flash
			if (grid[i][j] > '9') {
				flashes += flash(grid, i, j);
			}
		}
	}
	//zero out any flashed cells
	for (auto& row : grid) {
		for (auto& x : row) {
			if (x < '0') x = '0';
		}
	}
	return flashes;
}

uint32_t part1(std::vector<std::string> grid) {
	uint32_t flashes = 0;
	//count number of flashes each simulation step
	for (int i = 0; i < 100; i++) {
		flashes += simulation_step(grid);
	}
	return flashes;
}

uint32_t part2(std::vector<std::string> grid) {
	uint32_t step = 1;
	//run until we reach a point where all cells (10x10=100) flash at once
	while (simulation_step(grid) != 100) {
		step++;
	}
	return step;
}

int main() {
	std::vector<std::string> grid = parseInput();
	std::cout << "Part 1: " << part1(grid) << std::endl;
	std::cout << "Part 2: " << part2(grid) << std::endl;
}