#include <iostream>
#include <vector>
#include <unordered_map>

void solve()
{
	int n, tmp;
	std::vector<int> pillars;
	std::cin >> n;

	for (int i = 0; i < n; i++)
	{
		std::cin >> tmp;
		pillars.push_back(tmp);
	}
	std::unordered_map<int, int> freq;
	for (auto it = pillars.begin(); it != pillars.end(); it++)
	{
		freq[*it] += 1;
	}
	int max = 1;
	
	for (auto it = freq.begin(); it != freq.end(); it++)
	{
		if (it->second > max) max = it->second;
	}
	std::cout << n - max << '\n';

}

int main()
{
	int t;
	std::cin >> t;

	while (t --> 0) solve();
	return 0;
}
