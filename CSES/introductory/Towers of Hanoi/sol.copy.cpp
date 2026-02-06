#include <bits/stdc++.h>

// print correct moves to move all the disks from pile a or b to c,
// assuming input given such that disks are only ever entirely on a or entirely on b
void hanoi(int pile_a, int pile_b, int pile_c, int target)
{
    // the case with 1 disk is trivially moving that disk to c
    if (pile_a == 1)
    {
        std::cout << "1 " << target << "\n";
        return;
    } 
    if (pile_b == 1)
    {
        std::cout << "2 " << target << "\n";
        return;
    }
    if (pile_c == 1)
    {
        std::cout << "3 " << target << "\n";
        return;
    }

    // otherwise we move all but bottom disk to other pile, bottom disk to target, then other pile to target

    if (pile_a > 0) 
    {
        if (target == 3)
        {
            // disks to pile b, bottom to pile c, pile b to pile c
            hanoi(pile_a - 1, 0, 0, 2);
            std::cout << "1 3\n";
            hanoi(0, pile_a - 1, 0, 3);
        } else 
        {
            // disks to pile c, bottom to pile b, pile c to pile b 
            hanoi(pile_a - 1, 0, 0, 3);
            std::cout << "1 2\n";
            hanoi(0, 0, pile_a - 1, 2);
        }
    } else if (pile_b > 0) { // disks in pile b
        if (target == 3)
        {
            // disks to pile a, bottom to pile c, pile a to pile c
            hanoi(0, pile_b - 1, 0, 1);
            std::cout << "2 3\n";
            hanoi(pile_b - 1, 0, 0, 3);
        } else 
        {
            // disks to pile c, bottom to pile a, pile c to pile a
            hanoi(0, pile_b - 1, 0, 3);
            std::cout << "2 1\n";
            hanoi(0, 0, pile_b - 1, 1);
        }
    } else // pile c 
    {
        if (target == 1)
        {
            // disks to pile b, bottom to pile a, pile b to pile a
            hanoi(0, 0, pile_c - 1, 2);
            std::cout << "3 1\n";
            hanoi(0, pile_c - 1, 0, 1);
        } else // target == 2 
        {
            // disks to pile a, bottom to pile b, pile a to pile b
            hanoi(0, 0, pile_c - 1, 1);
            std::cout << "3 2\n";
            hanoi(pile_c - 1, 0, 0, 2);
        }
    }
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
    hanoi(n, 0, 0, 3);

    return 0;
}