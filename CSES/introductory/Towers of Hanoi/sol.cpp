#include <bits/stdc++.h>

void hanoi(int disk_count, int start, int dest)
{
    // trivially can move one disk directly to target
    if (disk_count == 1)
    {
        std::cout << start << " " << dest << "\n";
        return;
    }

    // otherwise, move all but bottom disk to intermediary column, move bottom to dest, then move all disks on intermediary column 

    // can use mod to find correct intermediary
    int intermediary { 3 - ((start + dest) % 3) };

    hanoi(disk_count - 1, start, intermediary);
    hanoi(1, start, dest);
    hanoi(disk_count - 1, intermediary, dest);
}


int main()
{
    int n {};
    std::cin >> n;

    // we could use vectors for moves and compute size from length, but we save the time and space needed for this by precomputing step count

    // the number of moves for size 1 is 1, for size n is 
    // number of moves to move disks except bottom to other pile, + number of moves to move bottom disk to target + number of moves to move from other pile to target
    // that is H(n) = 2H(n-1) + 1
    int num_moves { 1 };
    for (int i {1}; i < n; ++i) num_moves = 2 * num_moves + 1;
    std::cout << num_moves << "\n";

    hanoi(n, 1, 3);

    return 0;
}