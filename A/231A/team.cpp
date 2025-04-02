#include <iostream>

int main() {
	int problem_count;
	std::cin >> problem_count;
	int count = 0;
	for (int i = 0; i < problem_count; i++) {
		int sum = 0;
		int isSure;
		for (int j = 0; j < 3; j++) {
			std::cin >> isSure;
			sum += isSure;
		}
		if (sum > 1) count++;
	}
	std::cout << count << '\n';
	return 0;
}
