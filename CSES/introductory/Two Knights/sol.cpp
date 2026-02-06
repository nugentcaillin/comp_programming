#include <bits/stdc++.h>

int main()
{
    int max_board_length {};
    std::cin >> max_board_length;

    for (int board_length { 1 }; board_length <= max_board_length; ++board_length)
    {
        int board_squares { board_length * board_length };

        // the number of ways knights can be placed without attacking is number of ways you can place two knights - number of ways you can place two attacking knights

        long long ways_to_place { (long long)board_squares * (board_squares - 1) / 2 }; // combinations, can be ~10^20, need long long


        // knight can attack in 8 ways, only consider the 4 ways that are not mirror images to avoid duplicates
        // each way needs one space horizontal/vertical and two vertical/horizontal
        int ways_attacking { 4 * (board_length - 1) * std::max(board_length - 2, 0) };

        long long ways_not_attacking { ways_to_place - ways_attacking };

        std::cout << ways_not_attacking << "\n";
    }

    return 0;
}