#include <iostream>

int main() {
	int tests;
	std::cin >> tests;
	std::string a;
	std::string b;
	int len;
	for (int i = 0; i < tests; i++) {
		std::cin >> len >> a >> b;
		// can only move odd 1s in a 2 even in b and vice versa
		// -> can only create all zeroes in a if: 
		// 1. count of even 1s in a <= count of odd zeroes in b
		// 2. count of odd 1s in a <= count of odd zeroes in b
		int oddA = 0;
		int oddB = 0;
		int evenA = 0;
		int evenB = 0;
		for (int i = 0; i < len; i++) {
			if (a[i] == '1') {
				if (i % 2 == 0) {
					evenA++;
				} else {
					oddA++;
				}	
			}
			if (b[i] == '0') {
				if (i % 2 == 0) {
					evenB++;
				} else {
					oddB++;
				}
			}
		}
		if (oddA <= evenB && evenA <= oddB) {
			std::cout << "YES\n";
		} else {
			std::cout << "NO\n";
		}
	}
}
