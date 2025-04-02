#include <iostream>

bool canDivideEvenly(int kilos) {
	// an even number + an even number is an even number,
	// smallest even division is 2 + 2
	// so, for all even numbers greater than 2, can divide evenly
	return kilos % 2 == 0 && kilos > 3;
}

int main() {
	int kilos;
	std::cin >> kilos;
	if (canDivideEvenly(kilos)) {
		std::cout << "YES\n";
	} else {
		std::cout << "NO\n";
	}
	return 0;
}
