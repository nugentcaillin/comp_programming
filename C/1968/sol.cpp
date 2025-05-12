#include <iostream>

using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t --> 0)
	{
		int curr, total, n;

		cin >> n;
		total = 501;

		cout << total << " ";
		for (int i = 1; i < n; i++)
		{
			cin >> curr;
			total += curr;
			cout << total << " ";

		}
		cout << '\n';


	}
	return 0;
}
