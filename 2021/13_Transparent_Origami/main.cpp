#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <algorithm>

struct pair_hash
{
	template <class T1, class T2>
	std::size_t operator () (std::pair<T1, T2> const& pair) const
	{
		std::size_t h1 = std::hash<T1>()(pair.first);
		std::size_t h2 = std::hash<T2>()(pair.second);

		return h1 ^ h2;
	}
};

class Foldable_Transparent_Sheet {
public:
	Foldable_Transparent_Sheet(){
		m_markedPoints = new std::unordered_set<std::pair<int, int>, pair_hash>;
	}
	Foldable_Transparent_Sheet(std::string infile) {
		m_markedPoints = new std::unordered_set<std::pair<int, int>, pair_hash>;
		
		std::ifstream ifs(infile);
		std::string line;
		while (std::getline(ifs, line)) {
			if (line == "") continue;

			size_t d_pos = line.find(',');
			//if we found a comma, this is a coordinate
			if (d_pos != line.npos)
			{
				int x = stoi(line.substr(0, d_pos)),
					y = stoi(line.substr(d_pos + 1));
				maxX = std::max(maxX, x);
				maxY = std::max(maxY, y);

				m_markedPoints->insert({ x,y });
			}
			//else this is a fold instruction
			else
			{
				d_pos = line.find('=');
				m_folds.push({ line[d_pos - 1], stoi(line.substr(d_pos + 1)) });
			}
		}
	}
	~Foldable_Transparent_Sheet() {
		delete m_markedPoints;
	}
	uint32_t query() {
		return m_markedPoints->size();
	}
	void fold_up(int line) {
		std::unordered_set<std::pair<int, int>, pair_hash> *newSet = new std::unordered_set<std::pair<int, int>, pair_hash>;
		maxY = line;
		for (auto& [x, y] : *m_markedPoints) {
			//points do not move
			if (y < line) 
				newSet->insert({ x,y });
			else
				newSet->insert({ x, line - (y - line) });
		}
		delete m_markedPoints;
		m_markedPoints = newSet;
	}
	void fold_left(int line) {
		std::unordered_set<std::pair<int, int>, pair_hash> *newSet = new std::unordered_set<std::pair<int, int>, pair_hash>;
		maxX = line;
		for (auto& [x, y] : *m_markedPoints) {
			//points do not move
			if (x < line)
				newSet->insert({ x,y });
			else
				newSet->insert({ line - (x - line), y });
		}
		delete m_markedPoints;
		m_markedPoints = newSet;
	}
	void fold_once() {
		if (m_folds.size()) {
			if (m_folds.front().first == 'x')
				fold_left(m_folds.front().second);
			else
				fold_up(m_folds.front().second);
			m_folds.pop();
		}
	}
	void fold_all() {
		while (m_folds.size())
			fold_once();
	}
	void displayBoard() {
		std::vector<std::string> board(maxY, std::string(maxX, ' '));
		for (auto& [x, y] : *m_markedPoints)
			board[y][x] = '#';
		for (auto& row : board)
			std::cout << row << '\n';
	}

private:
	std::unordered_set<std::pair<int, int>, pair_hash> *m_markedPoints;
	std::queue<std::pair<char, int>> m_folds;
	int maxX, maxY;
};


int main() {
	Foldable_Transparent_Sheet sheet("input.txt");
	sheet.fold_once();
	std::cout << "Part 1: " << sheet.query() << std::endl;
	sheet.fold_all();
	std::cout << "Part 2: \n\n"; sheet.displayBoard();
	return 0;
}