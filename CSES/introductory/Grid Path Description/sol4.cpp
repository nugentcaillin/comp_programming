
#include <bits/stdc++.h>

const int GRID_SIZE { 7 };

// typedef std::array<std::array<int, GRID_SIZE>, GRID_SIZE> visited_t;
typedef std::vector<std::vector<bool>> visited_t;
typedef std::pair<int, int> direction_t; // row, col


int count { 0 };
visited_t visited(GRID_SIZE, std::vector<bool>(GRID_SIZE, false));
std::string path {};

direction_t direction_from_char(char c) {
    switch (c)
    {
    case 'U':
        return {-1, 0};
    case 'D':
        return {1, 0};
    case 'L': 
        return {0, -1};
    default:
        return {0, 1};
    }
}


const std::array<direction_t, 4> CARDINAL_DIRECTIONS 
{{
    { 0, 1 }
    , { 0, -1 }
    , { 1, 0 }
    , { -1, 0 }
}};

bool is_valid(int row, int col)
{
    return row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE && !visited.at(row).at(col);
}

bool is_early_return(int row, int col, int depth)
{
    return row == GRID_SIZE - 1 && col == 0 && depth < GRID_SIZE * GRID_SIZE - 1;
}


bool cuts_off_grid(int row, int col)
{
    bool cuts_off_vert { !is_valid(row + 1, col) && !is_valid(row - 1, col) && is_valid(row, col + 1) && is_valid(row, col - 1) };
    bool cuts_off_horiz { !is_valid(row, col + 1) && !is_valid(row, col - 1) && is_valid(row + 1, col) && is_valid(row - 1, col) };
    return cuts_off_vert || cuts_off_horiz;
}

// if we make a turn diagonal to end and both sides of end are free, we cannot make a solution
bool cuts_off_diagonally(int row, int col)
{
    if (row == GRID_SIZE - 2 && col == 1 && !visited.at(GRID_SIZE - 2).at(0) && !visited.at(GRID_SIZE - 1).at(1)) return true;
    return false;
}

void dfs(int row, int col, int depth)
{
    // if (!is_valid(row, col)) return;
    if (is_early_return(row, col, depth)) return;
    if (cuts_off_grid(row, col)) return;
    if (cuts_off_diagonally(row, col)) return;

    // if we have length 48 here, finished in correct place since any other solution will have been a return early condition
    if (depth == GRID_SIZE * GRID_SIZE - 1)
    {
        ++count;
        return;
    } 
    visited.at(row).at(col) = true;
    if (path.at(depth) != '?')
    {
        auto [drow, dcol] = direction_from_char(path.at(depth));
        if (is_valid(row + drow, col + dcol)) dfs(row + drow, col + dcol, depth + 1);
    } else 
    {
        for (auto [drow, dcol]: CARDINAL_DIRECTIONS) 
        {
            if (is_valid(row + drow, col + dcol)) dfs(row + drow, col + dcol, depth + 1);
        }
    }
    visited.at(row).at(col) = false;
}

int main()
{
    std::cin >> path;
    dfs(0, 0, 0);
    std::cout << count << "\n";
    return 0;
}