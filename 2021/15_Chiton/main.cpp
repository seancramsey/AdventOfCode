#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <iterator>
#include <limits>

class Solution {
public:
	Solution(){}
	Solution(std::string fPath) {
		std::ifstream ifs(fPath);
		std::string line;
		while (std::getline(ifs, line)) {
			m_risk_map.push_back({});
			for (auto& ch : line) {
				m_risk_map.back().push_back(int(ch-'0'));
			}
		}
	}
	//implement Djikstra's
	int run() {
		std::vector<std::vector<int>> min_cost_entering_coord(m_risk_map.size(), std::vector<int>(m_risk_map[0].size(), std::numeric_limits<int>::max()));
		std::priority_queue<pq_obj, std::vector<pq_obj>, pq_obj_compare> pq;

		pq.push({ 0,0,0 });
		while (pq.size()) {
			auto cur = pq.top(); pq.pop();

			if (cur.pathCost > min_cost_entering_coord[cur.x][cur.y])
				continue;
			for (auto& d : directions) {
				//if new X or new Y lies outside of grid, it is not a valid point
				int newX = cur.x + d.x;
				if (newX < 0 || newX >= m_risk_map.size())
					continue;
				int newY = cur.y + d.y;
				if (newY < 0 || newY >= m_risk_map[0].size())
					continue;
				//if the new cost is greater than or equal to the cost of another path that has reached this point then continuing is wasteful
				int newCost = cur.pathCost + m_risk_map[newX][newY];
				if (newCost >= min_cost_entering_coord[newX][newY])
					continue;
				min_cost_entering_coord[newX][newY] = newCost;
				pq.push({ newX, newY, newCost });
			}
		}
		return min_cost_entering_coord[min_cost_entering_coord.size() - 1][min_cost_entering_coord[0].size() - 1];
	}

	void expand_map_part2(size_t scale) {

		size_t  m = m_risk_map.size(),
			n = m_risk_map[0].size();
		m_risk_map.resize(m*scale);
		for (auto& row : m_risk_map)
			row.resize(n*scale);
		for (size_t i = 0; i < m; i++) {
			for (size_t j = 0; j < n; j++) {
				for (size_t y = 0; y < scale; y++) {
					for (size_t x = 0; x < scale; x++) {
						if (y == 0 && x == 0) continue;
						size_t	n_y = y * m + i,
								n_x = x * n + j;
						m_risk_map[n_y][n_x] = m_risk_map[i][j] + x + y;
						if (m_risk_map[n_y][n_x] > 9) {
							m_risk_map[n_y][n_x] %= 10;
							m_risk_map[n_y][n_x] += 1;
						}
					}
				}
			}
		}
	}

private:
	std::vector<std::vector<int>> m_risk_map;
	struct coord2d {
		int x, y;
		coord2d(int a, int b) : x(a), y(b) {}
	};
	struct pq_obj {
		int x, y, pathCost;
		pq_obj(int a, int b, int c) : x(a), y(b), pathCost(c){}
	};
	struct pq_obj_compare {
		bool operator()(pq_obj& a, pq_obj& b) {
			return a.pathCost > b.pathCost;
		}
	};
	std::vector<coord2d> directions = { {1,0}, {-1,0}, {0,1}, {0,-1}	};
};

int main() {
	Solution solution("input.txt");
	std::cout << "Part 1: " << solution.run() << std::endl;
	solution.expand_map_part2(5);
	std::cout << "Part 2: " << solution.run() << std::endl;
	return 0;
}