#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

void solve(vector<int>& sticks)
{
	// the partition where every partition has length one is always stable
	
	// so, for there to be multiple ways to partition we need to find one
	// continuous subsequence of at least 2 
	//
	
	// a subsequence can form a non degenerate triangle for all u v w iff
	// max() < 2 * min  
	


	for (int i = 1; i < sticks.size(); i++) 
	{
		if (max(sticks[i-1], sticks[i]) < 2 * min(sticks[i-1], sticks[i]))
		{
			cout << "Yes\n";
			return;
		}
	}
	cout << "No\n";
}


int main()
{
	int t;
	cin >> t;
	while (t --> 0) 
	{
		vector<int> sticks;
		int n, tmp;
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> tmp;
			sticks.push_back(tmp);
		}
		solve(sticks);

	}
	return 0;
}
