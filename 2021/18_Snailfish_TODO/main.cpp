#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <stack>
struct pair {
	int32_t value = -1;
	pair *left = nullptr, *right = nullptr;
	pair() {}
	~pair() {
		delete left;
		delete right;
	}
};
size_t find_one(std::string& eq, std::string delims, size_t i = 0) {
	std::vector<bool> chars(255, false);
	for (auto c : delims) {
		chars[c] = true;
	}
	for (; i < eq.size(); i++) {
		if (chars[eq[i]])
			return i;
	}
	return eq.npos;
}

pair* __make_pair_tree(std::string& eq, size_t& i) {
	pair* root = new pair;
	for (; i < eq.size(); i++) {
		if (eq[i] == '[') {
			root->left = __make_pair_tree(eq, ++i);
			root->right = __make_pair_tree(eq, ++i);
		}
		else if (eq[i] == ']') {
			return root;
		}
		else if (eq[i] == ',') {
			return root;
		}
		else {
			size_t d_pos = find_one(eq, ",]", i);
			root->value = std::stoll(eq.substr(i, d_pos - i));
			i = d_pos;
			return root;
		}
	}
	return root;
}
pair* make_pair_tree(std::string& eq) {
	size_t i = 0;
	return __make_pair_tree(eq, i);
}
void __print_tree(pair* root) {
	if (!root) {
		std::cout << "ERROR";
		return;
	}
	if (root->value > -1) {
		std::cout << root->value;
		return;
	}
	std::cout << '[';
	__print_tree(root->left);
	std::cout << ',';
	__print_tree(root->right);
	std::cout << ']';
}
void print_tree(pair* root) {
	__print_tree(root);
	std::cout << '\n';
	std::flush(std::cout);
}
int32_t magnitude(pair* eq) {
	int32_t mag_left = 0, mag_right = 0;
	if (eq->left->value > -1)
		mag_left = eq->left->value;
	else
		mag_left = magnitude(eq->left);
	if (eq->right->value > -1)
		mag_right = eq->right->value;
	else
		mag_right = magnitude(eq->right);
	return (3 * mag_left) + (2 * mag_right);
}
bool __split(pair* eq, bool& bsplit) {
	if (eq->value > -1) {
		if (!bsplit && eq->value >= 10) {
			bsplit = true;
			int32_t half = eq->value / 2;
			eq->left = new pair();
			eq->left->value = half;
			eq->right = new pair();
			eq->right->value = (eq->value & 1 ? half + 1 : half);
			eq->value = -1;
			return true;
		}
		return false;
	}
	return __split(eq->left,bsplit) || __split(eq->right,bsplit);
}
bool split(pair* eq) {
	bool b = false;
	return __split(eq, b);
}
bool __explode(pair* eq, int& l, int& r, bool& done, std::vector<int32_t*>& ptrs, size_t depth = 0) {
	if (eq->value > 9) return false;
	if (l == -1 && depth == 4 && eq->value == -1) {
		l = eq->left->value;
		r = eq->right->value;
		//std::cout << "(" << l << ',' << r << ')' << ' ';
		delete eq->left;
		eq->left = nullptr;
		delete eq->right;
		eq->right = nullptr;
		eq->value = 0;
		return false;
	}
	if (eq->value > -1) {
		if (l > -1) {
			//std::cout << "called: (" << l << ',' << r <<')' << std::endl;
			if(ptrs.size())
				*ptrs.back() += l;
			eq->value += r;
			return true;
		}
		ptrs.push_back(&eq->value);
		return false;
	}
	return __explode(eq->left, l,r,done,ptrs, depth + 1) || __explode(eq->right, l,r,done,ptrs, depth+1);

}
bool explode(pair* eq) {
	std::vector<int32_t*> numbers;
	int left = -1, right = -1;
	bool done = false;
	return __explode(eq, left, right, done, numbers);
}
void reduce(pair* eq) {
	bool done = false;
	print_tree(eq);
	while (!done) {
		while (explode(eq)) {
		//explode(eq);
			std::cout << "After Explode: ";
			print_tree(eq);
		}
		done = !split(eq);
		if (!done) {
			std::cout << "After Split  : ";
			print_tree(eq);
		}
	}
}
pair* add(pair* lhs, pair* rhs) {
	if (!lhs) 
		return rhs;
	else if (!rhs) 
		return lhs;
	else
	{
		pair* root = new pair;
		root->left = lhs;
		root->right = rhs;
		reduce(root);
		return root;
	}
}
int main() {	
	
	std::ifstream ifs("test.txt");
	std::string line;
	std::getline(ifs, line);

	pair* eq = make_pair_tree(line);
	while (std::getline(ifs, line)) {
		std::cout << "\nADDING\n";
		eq = add(eq, make_pair_tree(line));
		break;
	}

	std::cout << magnitude(eq);
	if (eq) delete eq;
}