#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

//create undirected graph from input file
std::unordered_map<std::string, std::vector<std::string>> parseInput() {
	std::ifstream ifs("input.txt");
	
	std::unordered_map<std::string, std::vector<std::string>> graph;
	std::string line;
	while (std::getline(ifs, line))
	{
		int delim_pos = line.find('-');
		std::string a = line.substr(0, delim_pos),
					b = line.substr(delim_pos + 1);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	return graph;
}

void p1DFS(std::unordered_map<std::string, std::vector<std::string>>& graph, std::string& curCave, std::unordered_set<std::string> smallCaves_visited, uint32_t& pathCount) {
	//if we reach the caves end we are finished 
	if (curCave == "end") {
		pathCount++;
		return;
	}
	//if the cave we are in (small cave only) has already been visited then this path is no bueno
	if (smallCaves_visited.find(curCave) != smallCaves_visited.end()) {
		return;
	}
	//if it is a "small cave" we add it to the visited set
	if (islower(curCave[0]))
		smallCaves_visited.insert(curCave);
	for (auto& cave : graph[curCave])
		p1DFS(graph, cave, smallCaves_visited, pathCount);
	if (islower(curCave[0]))
		smallCaves_visited.erase(curCave);
}

uint32_t part1(std::unordered_map<std::string, std::vector<std::string>>& graph) {
	std::unordered_set<std::string> smallCaves;
	uint32_t pathCount = 0;
	std::string curCave = "start";

	p1DFS(graph, curCave, smallCaves, pathCount);

	return pathCount;
}

void p2DFS(std::unordered_map<std::string, std::vector<std::string>>& graph, std::string& curCave, std::unordered_map<std::string, int> smallCaves_visited, uint32_t& pathCount, bool dblCave) {
	//if we reach the caves end we are finished 
	if (curCave == "end") {
		pathCount++;
		return;
	}
	//special case that the start cave can only be visited once 
	if (curCave == "start" && smallCaves_visited[curCave] == 1) {
		return;
	}

	bool f = false;
	if (islower(curCave[0])) {
		smallCaves_visited[curCave]++;
		//if this cave has been visted twice
		if (smallCaves_visited[curCave] >= 2) {
			//make sure it is the first to do so
			if (dblCave == false) {
				dblCave = true;
				f = true;
			}
			else {
				smallCaves_visited[curCave]--;
				return;
			}
		}
	}
	for (auto& cave : graph[curCave]) {
		p2DFS(graph, cave, smallCaves_visited, pathCount, dblCave);
	}
	if (islower(curCave[0])) {
		smallCaves_visited[curCave]--;
		if (f) {
			dblCave = false;
		}
	}
}


uint32_t part2(std::unordered_map<std::string, std::vector<std::string>>& graph) {
	std::unordered_map<std::string,int> smallCaves;
	for (auto& [k, v] : graph) {
		if (islower(k[0]))
			smallCaves[k] = 0;
	}

	uint32_t pathCount = 0;
	std::string curCave = "start";

	p2DFS(graph, curCave, smallCaves, pathCount, false);

	return pathCount;
}

int main() {
	std::unordered_map<std::string, std::vector<std::string>> graph = parseInput();
	std::cout << "Part 1: " << part1(graph) << std::endl;
	std::cout << "Part 2: " << part2(graph) << std::endl;
}