#include <iostream>

using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t --> 0)
	{
		int n, m, sx, sy, fx, fy;
		cin >> n >> m >> sx >> sy >> fx >> fy;

		// min number of obstacles is min to fully box in either the start or the end

		int box_start, box_end;
		box_start = 4 - (sx == 1) - (sy == 1) - (sx == n) - (sy == m);
		box_end = 4 - (fx == 1) - (fy == 1) - (fx == n) - (fy == m);
		cout << min(box_start, box_end) << '\n';
	}
	return 0;
}
