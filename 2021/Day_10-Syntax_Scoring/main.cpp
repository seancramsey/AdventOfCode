#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <iterator>
#include <algorithm>

std::vector<std::string> parseInput() {
	std::ifstream ifs("input.txt");

	std::vector<std::string> res;
	std::copy(std::istream_iterator<std::string>(ifs), std::istream_iterator<std::string>(), std::back_inserter(res));
	return res;
}


int score_badChunk(std::string& chunk) {
	//mp contains all closing bracket data; its opening bracket pair, and the score if its an error
	struct pair_score {
		char pair;
		int score;
		pair_score(char c, int s) : pair(c), score(s) {}
	};
	static const std::unordered_map<char, pair_score> mp = {
		{')', {'(',3}},
		{']', {'[',57}},
		{'}', {'{',1197}},
		{'>', {'<',25137}}
	};
	std::stack<char> st;
	for (auto ch : chunk) {
		//if closing bracket
		if (mp.find(ch) != mp.end()) {
			//if the bracket on the top of the stack is its pair, pop and continue
			if (st.size() && st.top() == mp.at(ch).pair)
				st.pop();
			//if the match fails; st is empty or mismatch, return score value
			else
				return mp.at(ch).score;

		}
		//elif opening bracket, push it to the stack
		else {
			st.push(ch);
		}
	}
	return 0;
}

int part1(std::vector<std::string>& data) {
	int score = 0;
	for (auto& chunk : data) {
		score += score_badChunk(chunk);
	}
	return score;
}


uint64_t score_autocomplete(std::string& chunk) {
	static const std::unordered_map<char, char> mp = {
		{')', '('},
		{']', '['},
		{'}', '{'},
		{'>', '<'}
	};

	uint64_t score = 0;
	std::stack<char> st;
	for (auto ch : chunk) {
		//if closing bracket
		if (mp.find(ch) != mp.end()) {
			//if the bracket on the top of the stack is its pair, pop and continue
			if (st.size() && st.top() == mp.at(ch))
				st.pop();
			//if the match fails; st is empty or mismatch, this is a corrupted string return 0;
			else
				return score;

		}
		//elif opening bracket, push it to the stack
		else {
			st.push(ch);
		}
	}

	//once we have checked for corrupt strings the state of the stack tells us whether or not it is incomplete
	static const std::unordered_map<char, uint32_t> sc = {
		{'(', 1},
		{'[', 2},
		{'{', 3},
		{'<', 4}
	};
	while (st.size()) {
		score = (5*score) + sc.at(st.top());
		st.pop();
	}
	return score;
}

uint64_t part2(std::vector<std::string>& data) {
	std::vector<uint64_t> scores;
	for (auto& chunk : data) {
		uint64_t score = score_autocomplete(chunk);
		if (score > 0)
			scores.push_back(score);
	}
	std::sort(scores.begin(), scores.end());
	
	std::cout << '\n';
	int i = 0;
	for (auto sc : scores) {
		std::cout << i++ << ' ' << sc << '\n';
	}
	std::cout << '\n';
	
	return scores[scores.size() / 2];
}


int main() {
	std::vector<std::string> data = parseInput();

	std::cout << "Part 1: " << part1(data) << std::endl;

	//part 2 fails and I have no idea why
	std::cout << "Part 2: " << part2(data) << std::endl;
	return 0;
}