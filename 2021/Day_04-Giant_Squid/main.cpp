#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <unordered_set>

int part1(std::vector<int>& numberStream,
	std::vector<std::vector<std::vector<int>>>& grids,
	std::vector<std::vector<int>>& rowSums,
	std::vector<std::vector<int>>& colSums) {

	int winning_id = -1,
		winning_num = 0;

	//for all values in the number stream
	for (auto x : numberStream) 
	{
		//look for it in each grid, and update relevant values
		for (int grid_id = 0; grid_id < grids.size(); grid_id++) 
		{
			for (int row_id = 0; row_id < grids[grid_id].size(); row_id++) 
			{
				for (int col_id = 0; col_id < grids[grid_id][row_id].size(); col_id++) 
				{
					if (grids[grid_id][row_id][col_id] == x) 
					{
						grids[grid_id][row_id][col_id] *= -1;

						rowSums[grid_id][row_id] -= x;
						colSums[grid_id][col_id] -= x;

						if (rowSums[grid_id][row_id] == 0 || colSums[grid_id][col_id] == 0) 
						{
							winning_id = grid_id;
							winning_num = x;
							goto WINNER_FOUND;
						}
						goto NEXT_GRID;
					}
				}
			}
		NEXT_GRID:;
		}
	}
WINNER_FOUND:;

	//now that a winner has been found, accumulate all remaining values;
	int sum = 0;
	for (auto& row : grids[winning_id]) {
		for (auto x : row) {
			if (x > 0) sum += x;
		}
	}

	return sum * winning_num;
}

int part2(std::vector<int>& numberStream,
	std::vector<std::vector<std::vector<int>>>& grids,
	std::vector<std::vector<int>>& rowSums,
	std::vector<std::vector<int>>& colSums) {
	//basically the same, but, run the simulation until the last board wins

	//maintain a list of ids still in the game;
	std::unordered_set<int> ids_still_playing;
	for (int i = 0; i < grids.size(); i++) {
		ids_still_playing.insert(ids_still_playing.end(), i);
	}


	int winning_id = -1,
		winning_num = 0;

	//for all values in the number stream
	for (auto x : numberStream)
	{
		//look for it in each grid, and update relevant values
		for (int grid_id = 0; grid_id < grids.size(); grid_id++)
		{
			//if this id has already won, we no longer need to check it
			if (ids_still_playing.find(grid_id) == ids_still_playing.end())
				continue;
			for (int row_id = 0; row_id < grids[grid_id].size(); row_id++)
			{
				for (int col_id = 0; col_id < grids[grid_id][row_id].size(); col_id++)
				{
					if (grids[grid_id][row_id][col_id] == x)
					{
						grids[grid_id][row_id][col_id] *= -1;

						rowSums[grid_id][row_id] -= x;
						colSums[grid_id][col_id] -= x;

						if (rowSums[grid_id][row_id] == 0 || colSums[grid_id][col_id] == 0)
						{
							winning_id = grid_id;
							winning_num = x;
							//remove this grid from the game
							ids_still_playing.erase(grid_id);
							//if all grids have been removed, that means the last grid processed is the final winner
							if (ids_still_playing.size() == 0) {
								goto WINNER_FOUND;
							}
						}
						goto NEXT_GRID;
					}
				}
			}
		NEXT_GRID:;
		}
	}
WINNER_FOUND:;

	//now that a winner has been found, accumulate all remaining values;
	int sum = 0;
	for (auto& row : grids[winning_id]) {
		for (auto x : row) {
			if (x > 0) sum += x;
		}
	}

	return sum * winning_num;
}


void parseDay4Input(std::vector<int>& numberStream, 
					std::vector<std::vector<std::vector<int>>>& grids,
					std::vector<std::vector<int>>& rowSums,
					std::vector<std::vector<int>>& colSums) 
{
	std::ifstream ifs("input.txt");
	std::string tempStr;

	//get first line
	{
		getline(ifs, tempStr);
		std::stringstream ss(tempStr);
		while (ss.good()) {
			getline(ss, tempStr, ',');
			numberStream.push_back(stoi(tempStr));
		}
	}

	//get all grids
	while (getline(ifs, tempStr)) {
		//if line is empty, this represents a new grid;
		if (tempStr == "") {
			grids.push_back(std::vector<std::vector<int>>());
			rowSums.push_back(std::vector<int>());
			colSums.push_back(std::vector<int>());
		}
		//otherwise we process the grid, row by row
		else {
			std::stringstream ss(tempStr);
			grids.back().push_back(std::vector<int>(std::istream_iterator<int>(ss), std::istream_iterator<int>()));

			if (colSums.back().size() == 0) {
				colSums.back().resize(grids.back().back().size());
			}
			int rowSum = 0;
			for (int i = 0; i < grids.back().back().size(); i++) {
				rowSum += grids.back().back()[i];
				colSums.back()[i] += grids.back().back()[i];
			}
			rowSums.back().push_back(rowSum);

		}
	}
}

void printInput(std::vector<int>& numStream,
	std::vector<std::vector<std::vector<int>>>& grids,
	std::vector<std::vector<int>>& rowSums,
	std::vector<std::vector<int>>& colSums) {

	for (auto x : numStream) {
		std::cout << x << ' ';
	}
	std::cout << "\n\n";

	for (int i = 0; i < grids.size(); i++) {

		for (int j = 0; j < colSums[i].size(); j++) {
			std::cout << std::setw(4) << colSums[i][j];
		}
		std::cout << "|\n";
		for (int j = 0; j < 25; j++)
			std::cout << '-';
		std::cout << '\n';

		for (int j = 0; j < grids[i].size(); j++) {
			for (int k = 0; k < grids[i][j].size(); k++) {
				std::cout << std::setw(4) << grids[i][j][k];
			}
			std::cout << '|' << std::setw(4) << rowSums[i][j];
			std::cout << '\n';
		}
		std::cout << '\n';
	}
}

int main() {
	std::vector<int> numStream;
	std::vector<std::vector<std::vector<int>>> grids;
	std::vector<std::vector<int>> rowSums, colSums;

	parseDay4Input(numStream, grids, rowSums, colSums);

	//printInput(numStream, grids, rowSums, colSums);

	std::cout << "Part 1: " << part1(numStream, grids, rowSums, colSums) << std::endl;
	std::cout << "Part 2: " << part2(numStream, grids, rowSums, colSums) << std::endl;
	return 0;
}