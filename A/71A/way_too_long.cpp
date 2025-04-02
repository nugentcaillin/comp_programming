#include <iostream>

int main() {
	int count;
	std::cin >> count;
	std::string word;
	for (int i = 0; i < count; i++) {
		std::cin >> word;
		if (word.size() <= 10) {
			std::cout << word << '\n';
		} else {
			std::cout << word.at(0);
			std::cout << word.size() - 2;
			std::cout << word.at(word.size() - 1);
			std::cout << '\n';
		}
	}
	return 0;
}
