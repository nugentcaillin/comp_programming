#include <iostream>

using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t --> 0)
	{
		int n, k;
		cin >> n >> k;

		// to be able to visit i islands,
		// (n - i) * i must be destroyed
		//
		// it takes n - 1 to remove one island, more to remove more,
		// but to remove all islands only takes n - 1

		if (k >= n - 1)
		{
			cout << 1 << '\n';
		} else 
		{
			cout << n << '\n';
		}
	}
	return 0;
}
