/*
ID: ncaillin
TASK: beads 
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>


int get_adjacent_length(std::string& beads, int start, int max, int direction)
{
	char char_used = 'w';
	int count = 0;
	int i { start };

	while ((count < max) && ((char_used == 'w') 
			|| (beads[i] == char_used) 
			|| beads[i] == 'w'))
	{
		if (char_used == 'w') char_used = beads[i];
		count++;
		i += direction;
		if (i == -1) i = beads.length() - 1;
		if (i == beads.length()) i = 0;
	}
	return count;
}


int main()
{
	std::ifstream in { "beads.in" };
	std::ofstream out { "beads.out" };
	
	std::string bead_sequence;
	int n {};

	in >> n >> bead_sequence;



	int max { 0 };
	for (int i { 0 }; i < n; i++)
	{
		int left_split { i - 1 };
		int right_split { i };
		if (left_split == -1) left_split = bead_sequence.length() - 1;
		if (right_split == bead_sequence.length()) right_split = 0;
		int curr { get_adjacent_length(bead_sequence, left_split, n, -1)
				   + get_adjacent_length(bead_sequence, right_split, n, 1)};
		if (curr > max) max = curr;
	}


	out << std::min(max, n) << std::endl;
	
	

	return 0;
}
