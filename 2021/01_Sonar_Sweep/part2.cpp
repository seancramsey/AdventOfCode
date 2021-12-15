#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

int main(){
	std::ifstream ifs("input.txt");	
	std::vector<int> input;
	
	std::copy(std::istream_iterator<int>(ifs), std::istream_iterator<int>(), std::back_inserter(input));
	
	int n = input.size(),
		countIncrease = 0;

	int prevWindowSum = input[0] + input[1] + input[2];
	for (int i = 3; i < n; i++) {
		int windowSum = input[i] + prevWindowSum - input[i - 3];
		if (prevWindowSum < windowSum)
			countIncrease++;
		prevWindowSum = windowSum;
	}
	std::cout<<countIncrease<<std::endl;
}