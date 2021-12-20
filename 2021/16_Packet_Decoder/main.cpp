#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

class Packet_Processor {
public:
	Packet_Processor() {}
	Packet_Processor(std::string fPath) : sumVers(0) {
		std::ifstream ifs(fPath);
		char ch;
		while (ifs.good()) {
			ifs >> ch;
			emplace_binary_from_hex(ch);
		}
		result = process();
	}

	size_t SumVersionNums() { return sumVers; }
	uint64_t GetResult() { return result; }
private:
	std::string m_str;
	int sumVers;
	uint64_t result;

	inline void emplace_binary_from_hex(char ch) {
		switch (ch)
		{
		case '0': m_str.append("0000"); break;
		case '1': m_str.append("0001"); break;
		case '2': m_str.append("0010"); break;
		case '3': m_str.append("0011"); break;
		case '4': m_str.append("0100"); break;
		case '5': m_str.append("0101"); break;
		case '6': m_str.append("0110"); break;
		case '7': m_str.append("0111"); break;
		case '8': m_str.append("1000"); break;
		case '9': m_str.append("1001"); break;
		case 'A': m_str.append("1010"); break;
		case 'B': m_str.append("1011"); break;
		case 'C': m_str.append("1100"); break;
		case 'D': m_str.append("1101"); break;
		case 'E': m_str.append("1110"); break;
		case 'F': m_str.append("1111"); break;
		default: break;
		}
	}
	inline int consume(size_t i) {
		int res = std::stoi(m_str.substr(0, i).c_str(), nullptr, 2);
		m_str.erase(m_str.begin(), m_str.begin() + i);
		return res;
	}

	uint64_t process() {
		int vers = consume(3);
		int type = consume(3);
		sumVers += vers;
		if (type == 4)
		{
			std::string load;
			while (consume(1)) {
				load.append(m_str.substr(0, 4));
				m_str.erase(m_str.begin(), m_str.begin() + 4);
			}
			load.append(m_str.substr(0, 4));
			m_str.erase(m_str.begin(), m_str.begin() + 4);

			return std::stoull(load, nullptr, 2);
		}
		else
		{
			std::vector<uint64_t> results;
			if (consume(1))
			{
				int count = consume(11);
				while (count--) {
					results.push_back(process());
				}
			}
			else
			{
				//count is in bits
				size_t count = consume(15);
				size_t tsize = m_str.size() - count;
				while (m_str.size() > tsize)
					results.push_back(process());
			}
			//process subpacket result
			uint64_t v;
			switch (type)
			{
				//sum
			case 0:
				v = 0;
				for (auto x : results) {
					v += x;
				}
				break;
				//product
			case 1:
				v = 1;
				for (auto x : results) {
					v *= x;
				}
				break;
				//minimum
			case 2:
				v = std::numeric_limits<uint64_t>::max();
				for (auto x : results) {
					v = std::min(v, x);
				}
				break;
				//maximum
			case 3:
				v = std::numeric_limits<uint64_t>::min();
				for (auto x : results) {
					v = std::max(v, x);
				}
				break;
				//greater than
			case 5:
				v = uint64_t(results[0] > results[1]);
				break;
				//less than
			case 6:
				v = uint64_t(results[0] < results[1]);
				break;
				//equal to
			case 7:
				v = uint64_t(results[0] == results[1]);
				break;

			default: break;
			}
			return v;
		}
		return 0;
	}
};

int main() {
	Packet_Processor p_stream("input.txt");

	std::cout << "Part 1: " << p_stream.SumVersionNums() << '\n';
	std::cout << "Part 2: " << p_stream.GetResult() << '\n';
	return 0;
}