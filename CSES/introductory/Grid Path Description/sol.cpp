#include <bits/stdc++.h>


const int GRID_SIZE { 7 };

typedef std::pair<int, int> direction_t;
typedef std::array<std::array<std::array<int, GRID_SIZE * GRID_SIZE>, GRID_SIZE>, GRID_SIZE> ways_t;
typedef std::array<std::array<bool, GRID_SIZE>, GRID_SIZE> visited_t;
typedef std::tuple<int, int, int, visited_t> state_t;

const direction_t foo { 0, 1 };


direction_t direction_from_char(char c)
{
    switch (c)
    {
    case 'D':
        return { 0 , 1 };
    case 'U':
        return { 0 , -1 };
    case 'R':
        return { 1 , 0 };
    default:
        return { -1 , 0 };
    }
}

direction_t inverse_direction_from_char(char c)
{
    switch (c)
    {
    case 'D':
        return { 0 , -1 };
    case 'U':
        return { 0 , 1 };
    case 'R':
        return { -1 , 0 };
    default:
        return { 1 , 0 };
    }
}


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

bool is_ending_square(int x, int y)
{
    return x == 0 && y == GRID_SIZE - 1;
}


int ways_to_reach(int x, int y, int moves, std::string& path, std::vector<std::vector<std::vector<int>>>& memo)
{
    if (moves == 1) return (x == 0 && y == 0) ? 1 : 0;
    if (memo.at(x).at(y).at(moves) != -1) return memo.at(x).at(y).at(moves);
    int sum { 0 };

    std::cout << x << ", " << y << ", " << moves << "\n";

    if (path.at(moves-1) == '?')
    {
        for (auto [dx, dy] : CARDINAL_DIRECTIONS)
        {
            if (is_valid_move(x, y, dx, dy)) sum += ways_to_reach(x + dx, y + dy, moves - 1, path, memo);
        }
    }
    else {
        auto [dx, dy] = inverse_direction_from_char(path.at(moves - 1));
        if (is_valid_move(x, y, dx, dy)) sum = ways_to_reach(x + dx, y + dy, moves - 1, path, memo);
    }
    memo.at(x).at(y).at(moves) = sum;
    return sum;
}


int main()
{
    std::string path {};
    std::cin >> path;
    int count { 0 };

    // it will take at most 48 moves to traverse a 7x7 grid
    // the amount of ways to traverse the entire grid ending at the bottom left
    // is the amount of ways to get from the top left to the bottom left taking exactly 48 moves
    // without repeat, bfs


    std::vector<std::vector<std::vector<int>>> memo(GRID_SIZE * GRID_SIZE, std::vector<std::vector<int>>(GRID_SIZE * GRID_SIZE, std::vector<int>(GRID_SIZE * GRID_SIZE, -1)));



    std::cout << ways_to_reach(0, GRID_SIZE - 1, 48, path, memo) << "\n";
}