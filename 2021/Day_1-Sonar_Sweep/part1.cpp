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
	for(int i = 1; i < n; i++){
		if(input[i] > input[i-1])
			countIncrease++;
	}
	std::cout<<countIncrease<<std::endl;
}