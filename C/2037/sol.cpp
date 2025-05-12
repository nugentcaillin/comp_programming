#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t --> 0)
	{
		int n;
		cin >> n;
		if (n < 5)
		{
			cout << -1 << '\n';
		} else 
		{
			// put pair of (4, 5) in middle, can guarantee
			// every other sum is even

			for (int i = 1; i <= n; i += 2)
			{
				if (i != 5) cout << i << " ";
			}
			cout << "5 4 ";
			for (int i = 2; i <= n; i += 2)
			{
				if (i != 4) cout << i << " ";
			}
			cout << "\n";
		}
	}
	return 0;
}
