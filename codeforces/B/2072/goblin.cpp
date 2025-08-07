#include <iostream>
#include <algorithm>

int main() {
	int test_count;
	int len;
	std::string s;
	std::cin >> test_count;

	for (int i = 0; i < test_count; i++) {
		std::cin >> len >> s;
		// to get the maximum number, 
		// assuming a - at each end
		// any _ that has a - between it and the next underscore
		// will be better off moving so that the underscores are together
		// as then those dashes will count towards both underscores
		// --> our optimum arrangement will have some number of
		// dashes, followed by all underscores, followed by some dashes
		//
		// following, the number of substrings we can make of -_-
		// would be the number of dashes to the left * number of 
		// underscores * dashes to right
		//
		// this product is maximised when dashes are as close to equal
		// as they can be, eg. 1 * 10 < 2 * 9
		
		long long int dash = 0;
		long long int under = 0;
		
		dash = std::count(s.begin(), s.end(), '-');
		under = std::count(s.begin(), s.end(), '_');
		
		long long int l = dash / 2;
		long long int r = dash - l;
		long long int ans = l * under * r;
		std::cout << ans << "\n";
	}
	return 0;
}
