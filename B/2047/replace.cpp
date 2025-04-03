#include <iostream>
#include <vector>

#define ALPHABET_LENGTH 26
void solve() {
	int n;
	std::string s;
	std::cin >> n >> s;
	std::vector<int> occ(ALPHABET_LENGTH, 0);

	// a string comprised entirely of one character has 1 permutation
	//
	// we get less permutations by increasing the relative occurence of the 
	// character that has the most appearances, and decreasing the
	// occurence of the one that has the least
	
	// map characters to their frequency
	
	for (std::string::iterator it = s.begin(); it != s.end(); it++) {
		occ.at(*it - 'a')++;
	}
	
	// get max and min 
	int min = 0;
	int max = 0;
	for (int i = 0; i < ALPHABET_LENGTH; i++) {
		if (occ.at(min) == 0) min = i;
		if (occ.at(i) == 0) continue;
		if (occ.at(i) < occ.at(min)) min = i;
		if (occ.at(i) > occ.at(max)) max = i;
	}

	char min_c = min + 'a';
	char max_c = max + 'a';


	// now, if min and max char are different, set an occurence of min 
	// to max
	std::string::iterator it;

	if (min_c != max_c) {
		for (it = s.begin(); *it != min_c; it++);
		*it = max_c;
	} else {
		// otherwise set any character to a character other than itself
		// for strings with identical chars we pick a random one,
		// can do nothing in this case
		for (it = s.begin(); it != s.end() && *it == *s.begin(); it++);
		if (it != s.end()) *it = *s.begin();
	}
	std::cout << s << "\n";
}

int main() {
	int tt;

	std::cin >> tt;

	while (tt --> 0) {
		solve();
	} 

	return 0;
}
