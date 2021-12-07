#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <limits>
#include <unordered_set>
#include <math.h>

struct Line {
	int x1,y1,x2,y2;
	Line(int a, int b, int a1, int b1) : x1(a), y1(b), x2(a1), y2(b1) {}
};

void parseInput(std::vector<Line>& lines, int& maxX, int& maxY) {
	std::ifstream ifs("input.txt");
	
	std::string line;
	while (std::getline(ifs, line)) {
		std::string delim = " -> ";
		int delimPos = line.find(delim);

		std::string 
			start = line.substr(0, delimPos),
			end = line.substr(delimPos+delim.size());

		int s = start.find(','),
			e = end.find(',');

		lines.emplace_back(
			stoi(start.substr(0, s)),
			stoi(start.substr(s+1)),
			stoi(end.substr(0, e)),
			stoi(end.substr(e+1))
		);

		maxX = std::max(maxX, lines.back().x1);
		maxX = std::max(maxX, lines.back().x2);

		maxY = std::max(maxY, lines.back().y1);
		maxY = std::max(maxY, lines.back().y2);
	}
}

//DDA Line drawing algo
void drawLine(std::vector<std::vector<int>>& grid, Line const& line) {
	int //absolute slopes of x and y component
		dx = abs(line.x2 - line.x1),
		dy = abs(line.y2 - line.y1),
		//sign of each slope
		sx = line.x2 >= line.x1 ? 1 : -1,
		sy = line.y2 >= line.y1 ? 1 : -1,
		//number of steps (max pixels) to draw
		steps = std::max(dx, dy),
		//amount to move each step
		xinc = ceil(dx / float(steps)) * sx,
		yinc = ceil(dy / float(steps)) * sy,
		//initial points
		x = line.x1, y = line.y1;
	do {
		grid[y][x]++;
		x += xinc;
		y += yinc;
	} while (steps--);
}

int countOverlaps(std::vector<std::vector<int>>& grid) {
	int intersections = 0;
	//std::cout << "\n\n";
	for (auto& row : grid) {
		for (auto& x : row) {
			//std::cout << x << ' ';
			if (x >= 2)
				intersections++;
		}
		//std::cout << '\n';
	}
	//std::cout << '\n';
	return intersections;
}

int part1(std::vector<Line> const& lines, const int& maxX, const int& maxY) {
	std::vector<std::vector<int>> grid(maxY+1, std::vector<int>(maxX+1, 0));

	for (auto& line : lines) {
		//for part 1 we only consider axis aligned lines
		if (line.x1 == line.x2 || line.y1 == line.y2) {
			drawLine(grid, line);
		}
	}
	return countOverlaps(grid);
}
int part2(std::vector<Line> const& lines, const int& maxX, const int& maxY) {
	std::vector<std::vector<int>> grid(maxY+1, std::vector<int>(maxX+1, 0));
	//count all lines
	for (auto& line : lines) {
		drawLine(grid, line);
	}
	return countOverlaps(grid);
}

int main() {
	int maxX = std::numeric_limits<int>::min(),
		maxY = std::numeric_limits<int>::min();
	std::vector<Line> lines;
	parseInput(lines, maxX, maxY);

	std::cout << "Part 1: " << part1(lines, maxX, maxY) << std::endl;
	std::cout << "Part 2: " << part2(lines, maxX, maxY) << std::endl;

	return 0;
}