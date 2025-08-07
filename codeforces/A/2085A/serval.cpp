#include <iostream>

bool can_be_made_universal(std::string s, int k) {
	// if k = 0 must already be universal
	
	// otherwise, if reverse is lexographically greater, can swap
	// the first character they differ at to make it universal
	//
	// if lexographically the same i.e palindrome, so long as all characters
	// are not identical, can always make one swap to make it universal
	std::string::iterator it = s.begin();
	std::string::reverse_iterator rit = s.rbegin();

	if (k == 0) {
		for (; it != s.end(); it++, rit++) {
			if (*rit < *it) return false;
			if (*rit > *it) return true;
		}
		return false;
	}

	// check if has any differing characters i.e. all characters do not
	// equal first char
	
	char first = *it;
	for (; it != s.end(); it++) {
		if (*it != first) return true;
	}
	return false;

}

int main() {
	int test_cases;
	std::cin >> test_cases;
	for (int i = 0; i < test_cases; i++) {
		int length;
		int k;
		std::string s;
		std::cin >> length >> k >> s;
		if (can_be_made_universal(s, k)) {
			std::cout << "YES\n";
		} else {
			std::cout << "NO\n";
		}
	}
	return 0;
}
