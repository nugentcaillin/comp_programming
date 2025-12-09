#include <bits/stdc++.h>

const int GRID_SIZE { 7 };

typedef std::pair<int, int> direction_t;

const std::array<direction_t, 4> CARDINAL_DIRECTIONS 
{{
    { 0, 1 }
    , { 0, -1 }
    , { 1, 0 }
    , { -1, 0 }
}};


bool is_valid_move(int x, int y, int dx, int dy)
{
    return x + dx >= 0 && x + dx < GRID_SIZE && y + dy >= 0 && y + dy < GRID_SIZE;
}


int paths (int x, int y, int depth, std::vector<std::vector<std::vector<long long>>>& memo)
{
    // std::cout << x << ", " << y << ", " << depth << "\n";
    if (memo.at(x).at(y).at(depth) >= 0) return memo.at(x).at(y).at(depth);
    if (depth == 0)
    {
        if (x == 0 && y == 0) 
        {
            std::cout << "ret 1\n";
            memo.at(x).at(y).at(depth) = 1;
            return 1;
        }
        memo.at(x).at(y).at(depth) = 0;
        return 0;
    }

    int sum { 0 };
    for (auto [dx, dy]: CARDINAL_DIRECTIONS)
    {
        if (is_valid_move(x, y, dx, dy)) sum += paths(x+dx, y+dy, depth - 1, memo);
    }
    memo.at(x).at(y).at(depth) = sum;
    return sum;
}


int main()
{
    // to get to the bottom left traversing every cell, we must make 48 moves.
    // the number of down moves needs to be 6 more than up moves
    // number of left and right is equal
    // and sum of up, down, left and right is equal
    // also, down, left and right must all be >= 6

    std::vector<std::vector<std::vector<long long>>> memo(GRID_SIZE, std::vector<std::vector<long long>>(GRID_SIZE, std::vector<long long>(GRID_SIZE * GRID_SIZE, -1)));


    std::cout << paths(0, 6, 48, memo);
    for (int i {0}; i < 49; ++i)
    {
        std::cout << "MOVES: " << i << "\n";
        for (int x {0}; x < 7; ++x)
        {
            for (int y {0}; y < 7; ++y)
            {
                std::cout << memo.at(y).at(x).at(i) << " ";       
            }
            std::cout << "\n";
        }
    }
}