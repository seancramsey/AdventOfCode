#include <iostream>
#include <fstream>
#include <string>

bool explode(std::string& eq, size_t index) {
	
}

void reduce(std::string& eq) {
	size_t pair_depth = 0;

	while (true) {
		for (int i = 0; i < eq.size(); i++) {
			if (eq[i] == '[') {
				pair_depth++;
			}
			else if (eq[i] == ']')
				pair_depth--;
			if (pair_depth == 4 && explode(eq, i + 1)) break;
		}
	}
}

void add(std::string& lhs, std::string& rhs) {
	if (lhs == "") lhs = rhs;

	else
	{
		lhs = '[' + lhs + ',' + rhs + ']';
		reduce(lhs);
	}
}

int main() {
	std::string eq = "";

	std::ifstream ifs("test.txt");
	std::string line;
	while (std::getline(ifs, line)) {
		add(eq, line);
	}
}