#include <iostream>

void solve() {
	int n;
	int time;
	int min;
	int l;
	int r;
	bool possib = true;
	std::cin >> n;

	// we can indefinitely reset clocks if and only if for 
	// every clock we have time to reset every other
	// clock before that one reaches 0.
	//
	// since we can move one clock over or reset current clock every 
	// time step, the minimum time that each clock must have is the 
	// distance to travel to each other clock while having time to make 
	// it back to itself
	//
	// this is means we must move 2 * max(num to left, num to right) times
	// plus one to make it back to the clock
	for (int i = 0; i < n; i++) {
		std::cin >> time;
		l = i;
		r = n - i - 1;
		min = std::max(l, r) * 2 + 1;
		if (time < min) {
			possib = false;
		}
	}
	if (possib) {
		std::cout << "YES\n";
	} else {
		std::cout << "NO\n";
	}

}

int main() {
	int tt;
	std::cin >> tt;
	while (tt --> 0) {
		solve();
	}

	return 0;
}
