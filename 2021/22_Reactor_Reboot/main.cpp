#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

struct Range {
	int first, last;
	Range() : first(0), last(0) {}
	Range(int x, int y) {
		if (x > y) std::swap(x, y);
		first = x;
		last = y;
	}
};
//this class effectively creates an octree, however because I am fond of silly things, each node has *potentially* 27 children
class Cuboid {
public:
	Cuboid() 
		: m_xRange({ 0,0 }), m_yRange({ 0,0 }), m_zRange({0,0}), m_state(false)
	{}
	Cuboid(int min, int max)
		: m_xRange({ min,max }), m_yRange({ min,max }), m_zRange({ min,max }), m_state(false)
	{}
	Cuboid(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax, bool state)
		: m_xRange({ xmin,xmax }), m_yRange({ ymin,ymax }), m_zRange({ zmin,zmax }), m_state(state)
	{}
	~Cuboid() {}

	void Apply(std::unique_ptr<Cuboid>& other) {
		if (IntersectsWith(other))
		{
			if (!m_children.empty()) 
			{
				for (auto& c : m_children)
					c->Apply(other);
			}
			else //we are a "leaf node"
			{
				//if there will be no change in state, skip
				if (other->m_state == m_state)
					return;
				//clamp the Cuboid we are applying to the bounds of *this Cuboid
				int xFirst = std::max(other->m_xRange.first, m_xRange.first),
					xLast = std::min(other->m_xRange.last, m_xRange.last),
					yFirst = std::max(other->m_yRange.first, m_yRange.first),
					yLast = std::min(other->m_yRange.last, m_yRange.last),
					zFirst = std::max(other->m_zRange.first, m_zRange.first),
					zLast = std::min(other->m_zRange.last, m_zRange.last);
				//if the clamped cuboid is the completely covers the *this cuboid, just set state
				if (xFirst == m_xRange.first && xLast == m_xRange.last && yFirst == m_yRange.first && yLast == m_yRange.last && zFirst == m_zRange.first && zLast == m_zRange.last) 
				{
					m_state = other->m_state;
					return;
				}
				//each pair represents the ranges of each dimension in a 3x3x3 cube, 27 subCubes
				std::vector<std::vector<int>> vals {
				/*xVals*/{ xFirst, xLast,	 m_xRange.first, xFirst - 1,	xLast + 1, m_xRange.last },
				/*yVals*/{ yFirst, yLast,	 m_yRange.first, yFirst - 1,	yLast + 1, m_yRange.last },
				/*zVals*/{ zFirst, zLast,	 m_zRange.first, zFirst - 1,	zLast + 1, m_zRange.last }
				};
				//eliminate pairs that result in one dimension having length<=0
				for (size_t i = 0; i < 3; i++) {
					for (int j = vals[i].size() - 2; j >= 0; j -= 2) {
						if(vals[i][j] > vals[i][j+1])
							vals[i].erase(vals[i].begin() + j, vals[i].begin() + j + 2);
					}
				}
				//Create child cuboids, because of how vals[i] is sorted, the target Cuboid will be the first child
				for (size_t x = 0; x < vals[0].size() - 1; x += 2)
				{
					for (size_t y = 0; y < vals[1].size() - 1; y += 2)
					{
						for (size_t z = 0; z < vals[2].size() - 1; z += 2)
						{
							m_children.push_back(std::unique_ptr<Cuboid>(new Cuboid(vals[0][x], vals[0][x + 1], vals[1][y], vals[1][y + 1], vals[2][z], vals[2][z + 1], m_state)));
						}
					}
				}
				m_children[0]->m_state = other->m_state;
			}
		}
		return;
	}
	uint64_t CountLights() {
		uint64_t lights = 0;
		if (m_children.size()) {
			for (auto& child : m_children) {
				lights += child->CountLights();
			}
		}
		else if (m_state){
			lights = Area();
		}
		return lights;
	}
	//prints the entire tree structure, use at your own risk
	void print(size_t depth = 0) {
		std::string spaces(depth, '\t');
		//if (m_state || m_children.size()) {
			if (depth)
				std::cout << spaces << '|';
			std::cout <<
				'\n' << spaces << "x:(" << m_xRange.first << ',' << m_xRange.last << ')' <<
				" y:(" << m_yRange.first << ',' << m_yRange.last << ')' <<
				" z:(" << m_zRange.first << ',' << m_zRange.last << ')' <<
				'\n' << spaces << "State: " << (m_state ? "ON" : "OFF") <<
				'\n' << spaces << "Children: " << m_children.size() << std::endl;
		//}
		for (auto& child : m_children) {
			child->print(depth + 1);
		}
	}
	int XLength() {
		return m_xRange.last - m_xRange.first + 1;
	}
	int YLength() {
		return m_yRange.last - m_yRange.first + 1;
	}
	int ZLength() {
		return m_zRange.last - m_zRange.first + 1;
	}
	uint64_t Area() {
		return uint64_t(1) * XLength() * YLength() * ZLength();
	}
	bool IntersectsWith(std::unique_ptr<Cuboid>& other) {
		return (
			(other->m_xRange.first <= m_xRange.last && other->m_xRange.last >= m_xRange.first) &&
			(other->m_yRange.first <= m_yRange.last && other->m_yRange.last >= m_yRange.first) &&
			(other->m_zRange.first <= m_zRange.last && other->m_zRange.last >= m_zRange.first)
		);
	}
private:
	Range m_xRange, m_yRange, m_zRange;
	bool m_state;
	std::vector<std::unique_ptr<Cuboid>> m_children;
};


std::unique_ptr<Cuboid> processLine(std::string& line) {
	size_t cur_index = 0;
	size_t delim_pos = line.find(' ');

	bool state = (line.substr(0, delim_pos) == "on" ? true : false);
	
	cur_index = delim_pos + 3;
	delim_pos = line.find('.', cur_index);
	int xmin = stoi(line.substr(cur_index, delim_pos - cur_index));
	cur_index = delim_pos + 2;
	delim_pos = line.find(',', cur_index);
	int xmax = stoi(line.substr(cur_index, delim_pos - cur_index));

	cur_index = delim_pos + 3;
	delim_pos = line.find('.', cur_index);
	int ymin = stoi(line.substr(cur_index, delim_pos - cur_index));
	cur_index = delim_pos + 2;
	delim_pos = line.find(',', cur_index);
	int ymax = stoi(line.substr(cur_index, delim_pos - cur_index));

	cur_index = delim_pos + 3;
	delim_pos = line.find('.', cur_index);
	int zmin = stoi(line.substr(cur_index, delim_pos - cur_index));
	cur_index = delim_pos + 2;
	int zmax = stoi(line.substr(cur_index));

	return std::unique_ptr<Cuboid>(new Cuboid( xmin, xmax, ymin, ymax, zmin, zmax, state ));
}

int main() {
	std::vector<std::unique_ptr<Cuboid>> processCuboids;
	std::fstream ifs("input.txt");
	std::string line;
	while (std::getline(ifs, line)) {
		processCuboids.push_back(std::move(processLine(line)));
	}
	//PART 1
	{
		Cuboid tinyCube(-50, 50);
		for (auto& c : processCuboids) {
			tinyCube.Apply(c);
		}
		std::cout << "Part 1: " << tinyCube.CountLights() << std::endl;
	}
	//PART 2
	{
		Cuboid maximumCube(-200'000, 200'000);
		for (auto& c : processCuboids) {
			maximumCube.Apply(c);
		}
		std::cout << "Part 2: " << maximumCube.CountLights() << std::endl;
	}

	return 0;
}