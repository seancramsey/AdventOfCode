#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

std::vector<std::string> parseFile() {
	std::ifstream ifs("input.txt");

	std::vector<std::string> data;
	std::string tempStr;
	while (std::getline(ifs, tempStr)) {
		data.push_back(std::move(tempStr));
	}
	return data;
}

struct Point {
	int x, y;
	Point(int a, int b) : x(a), y(b) {}
};

int part1(std::vector<std::string>& heightmap, std::vector<Point>& coords) {
	int N = heightmap.size(),
		M = heightmap[0].size();
	int answer = 0;
	//TL
	if (heightmap[0][1] > heightmap[0][0] &&
		heightmap[1][0] > heightmap[0][0]) {
		answer += static_cast<int>(heightmap[0][0] - '0') + 1;
		coords.push_back({ 0,0 });
	}
	//TR
	if (heightmap[0][M-2] > heightmap[0][M-1] &&
		heightmap[1][M-1] > heightmap[0][M-1]) {
		answer += static_cast<int>(heightmap[0][M - 1] - '0') + 1;
		coords.push_back({ 0,M-1 });
	}
	//BL
	if (heightmap[N-1][1] > heightmap[N-1][0] &&
		heightmap[N-2][0] > heightmap[N-1][0]) {
		answer += static_cast<int>(heightmap[N - 1][0] - '0') + 1;
		coords.push_back({ N-1,0 });
	}
	//BR
	if (heightmap[N-1][M-2] > heightmap[N-1][M-1] &&
		heightmap[N-2][M-1] > heightmap[N-1][M-1]) {
		answer += static_cast<int>(heightmap[N - 1][M - 1] - '0') + 1;
		coords.push_back({ N-1,M-1 });
	}
	
	//vertical border
	for (int i = 1; i < N - 1; i++) {
		if (heightmap[i - 1][0] > heightmap[i][0] &&
			heightmap[i + 1][0] > heightmap[i][0] &&
			heightmap[i][1] > heightmap[i][0] )
		{
			answer += static_cast<int>(heightmap[i][0] - '0') + 1;
			coords.push_back({ i,0 });
		}
		
		if (heightmap[i - 1][M-1] > heightmap[i][M-1] &&
			heightmap[i + 1][M-1] > heightmap[i][M-1] &&
			heightmap[i][M-2] > heightmap[i][M-1] )
		{
			answer += static_cast<int>(heightmap[i][M-1] - '0') + 1;
			coords.push_back({ i,M-1 });
		}
	}
	//horizontal border
	for (int j = 1; j < M - 1; j++) {
		if (heightmap[0][j - 1] > heightmap[0][j] &&
			heightmap[0][j + 1] > heightmap[0][j] &&
			heightmap[1][j] > heightmap[0][j] )
		{
			answer += static_cast<int>(heightmap[0][j] - '0') + 1;
			coords.push_back({ 0,j });
		}
		if (heightmap[N - 1][j - 1] > heightmap[N - 1][j] &&
			heightmap[N - 1][j + 1] > heightmap[N - 1][j] &&
			heightmap[N-2][j] > heightmap[N-1][j])
		{
			answer += static_cast<int>(heightmap[N - 1][j] - '0') + 1;
			coords.push_back({ N-1,j });
		}
	}
	//remaining
	for (int i = 1; i < N - 1; i++) {
		for (int j = 1; j < N - 1; j++) {
			if (heightmap[i - 1][j] > heightmap[i][j] &&
				heightmap[i + 1][j] > heightmap[i][j] &&
				heightmap[i][j - 1] > heightmap[i][j] &&
				heightmap[i][j + 1] > heightmap[i][j]) 
			{
				answer += static_cast<int>(heightmap[i][j] - '0') + 1;
				coords.push_back({ i,j });
			}
		}
	}
	return answer;
}

//finding the largest basins requires a breadth first graph search
int bfs(std::vector<std::string>& heightmap, std::vector<std::vector<bool>>& visited, Point coord) {
	std::queue<Point> q;
	q.push(coord);

	int size = 0;
	while (q.size()) {
		Point curr = q.front();
		q.pop();

		//if curr is valid, i.e. not already visited and not a peak
		if (!visited[curr.x][curr.y] && heightmap[curr.x][curr.y] != '9') {
			visited[curr.x][curr.y] = true;
			size++;

			for (int i = -1; i <= 1; i++) {
				int newX = curr.x + i,
					newY = curr.y + i;

				//if the point is within the heightmap and if higher than the current postion
				if(0 <= newX && newX < heightmap.size() && heightmap[newX][curr.y] >= heightmap[curr.x][curr.y])
					q.push({ newX, curr.y });
				if (0 <= newY && newY < heightmap[0].size() && heightmap[curr.x][newY] >= heightmap[curr.x][curr.y])
					q.push({ curr.x, newY });
			}
		}
		
	}
	return size;
}

int part2(std::vector<std::string>& heightmap, std::vector<Point>& coords) {
	std::vector<std::vector<bool>> visited(heightmap.size(), std::vector<bool>(heightmap[0].size(), false));
	std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
	//std::cout << '\n';
	for (auto& coord : coords) {
		int b_size = bfs(heightmap, visited, coord);
		//std::cout << b_size << '\n';
		pq.push(b_size);

		if (pq.size() > 3)  
			pq.pop();
	}

	int product = 1;
	while (pq.size()) {
		product *= pq.top();
		pq.pop();
	}
	return product;
}

int main() {
	std::vector<std::string> heightmap = parseFile();
	std::vector<Point> low_points;


	std::cout << "Part 1: " << part1(heightmap, low_points) << std::endl;
	std::cout << "Part 2: " << part2(heightmap, low_points) << std::endl;

	return 0;
}