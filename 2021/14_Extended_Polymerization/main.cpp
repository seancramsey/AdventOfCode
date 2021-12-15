#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>

class Polymerization_Thing {
public:
	Polymerization_Thing() {};
	Polymerization_Thing(std::string fPath) {
		std::ifstream ifs(fPath);
		//get template;
		std::getline(ifs, m_polymer_template);
		std::string line;
		//get empty line
		std::getline(ifs, line);
		//get rule set
		while (std::getline(ifs, line)) {
			m_insertion_rules[line.substr(0, 2)] = line.back();
		}
	}
	void reset_counts() {
		m_compound_counts.clear();
		for (auto& c : m_polymer_template) {
			m_compound_counts[c]++;
		}
		m_pair_counts.clear();
		for (rsize_t i = 0; i < m_polymer_template.size() - 1; i++) {
			m_pair_counts[m_polymer_template.substr(i, 2)]++;
		}
	}
	uint64_t run(size_t steps) {
		reset_counts();

		for (size_t i = 0; i < steps; i++) {
			std::unordered_map<std::string, uint64_t> temp;
			for (auto& [pair, c] : m_pair_counts) {
				char ch = m_insertion_rules[pair];
				m_compound_counts[ch] += c;

				temp[pair.substr(0, 1) + ch] += c;
				temp[ch + pair.substr(1, 1)] += c;
			}
			m_pair_counts = std::move(temp);
		}
		auto mmax = std::numeric_limits<uint64_t>::min();
		auto mmin = std::numeric_limits<uint64_t>::max();;
		for (auto& [k, v] : m_compound_counts) {
			mmax = std::max(mmax, v);
			mmin = std::min(mmin, v);
		}
		return mmax - mmin;
	}
private:
	std::string m_polymer_template;
	std::unordered_map<std::string, char> m_insertion_rules;
	std::unordered_map<char, uint64_t> m_compound_counts;
	std::unordered_map<std::string, uint64_t> m_pair_counts;
};

int main() {
		Polymerization_Thing pt("input.txt");
		std::cout << "Part 1: " << pt.run(10) << std::endl;
		std::cout << "Part 2: " << pt.run(40) << std::endl;

	return 0;
}