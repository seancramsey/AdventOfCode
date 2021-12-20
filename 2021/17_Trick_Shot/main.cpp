#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <array>

//GLOBALS
int x1 = 20, x2 = 30, y1 = -10, y2 = -5;


int part1() {
	int ay = abs(y1);
	return ay * (ay-1) / 2;
}

struct my_hash
{
	std::size_t operator () (std::array<int, 2> const& pair) const
	{
		std::size_t h1 = std::hash<int>()(pair[0]);
		std::size_t h2 = std::hash<int>()(pair[1]);

		return h1 ^ h2;
	}
};

bool hit(int xv, int yv) {
	int x_p = 0, y_p = 0;
	for (int step = 0; step <= abs(y1) * 2 + 1; step++) {
		x_p += xv;
		y_p += yv;
		if ((x1 <= x_p && x_p <= x2) && (y1 <= y_p && y_p <= y2)) {
			return true;
		}
		xv = (xv >= 0 ? (xv > 0 ? xv - 1 : 0) : xv + 1);
		yv--;
	}
	
	return false;
}

//brutal force FTW
int part2() {
	std::unordered_set<std::array<int, 2>, my_hash> initial_Velocities;
	for (int xv = -abs(x1); xv <= abs(x2); xv++) {
		for (int yv = -abs(y1); yv <= abs(y1); yv++) {
			std::array<int, 2> a{ xv,yv };

			if (initial_Velocities.find(a) == initial_Velocities.end() && hit(xv, yv))
				initial_Velocities.insert(a);
		}
	}
	return initial_Velocities.size();
}

int main() {
#define TEST false
#if TEST == false
	{
		std::ifstream ifs("input.txt");
		std::string line;
		std::getline(ifs, line);
		size_t st, ed;
		st = line.find('=') + 1;
		ed = line.find('.', st);
		x1 = stoi(line.substr(st, ed - st));
		st = ed + 2;
		ed = line.find(',', st);
		x2 = stoi(line.substr(st, ed - st));
		st = line.find('=', ed) + 1;
		ed = line.find('.', st);
		y1 = stoi(line.substr(st, ed - st));
		st = ed + 2;
		y2 = stoi(line.substr(st));
	}
#endif
	std::cout << "Part 1: " << part1() << std::endl;
	std::cout << "Part 2: " << part2() << std::endl;
	return 0;
}