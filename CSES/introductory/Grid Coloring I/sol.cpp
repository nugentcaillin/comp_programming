#include <bits/stdc++.h>

const int FOUND { 0 };
const int NOT_FOUND { 1 };
const std::array<char, 4> colours {'A', 'B', 'C', 'D'};


// convert grid to one obeying problem constraints if possible
int dfs(std::vector<std::vector<char>>& grid, int row, int col)
{
    // correctly changed grid if we have changed every element without conflict
    if (row == grid.size()) return FOUND;

    char original_colour { grid.at(row).at(col) };
    for (char colour : colours)
    {
        // cannot be same colour as current cell
        if (grid.at(row).at(col) == colour) continue;

        // only need to check up and left due to us doing dfs left to right up to down
        if (col > 0 && grid.at(row).at(col - 1) == colour) continue; // left
        if (row > 0 && grid.at(row - 1).at(col) == colour) continue; // up

        grid.at(row).at(col) = colour;
        int next_row { col == (int)grid.at(row).size() - 1 ? row + 1 : row }; // if last col, need to move to new row
        int next_col { (col + 1) % (int)grid.at(row).size() };

        if (dfs(grid, next_row, next_col) == FOUND) return FOUND;
    }
    // if we are backtracking, reset grid
    grid.at(row).at(col) = original_colour;
    return NOT_FOUND;
}


int main()
{
    int rows {};
    int cols {};
    std::cin >> rows >> cols;
    std::vector<std::vector<char>> grid(rows, std::vector<char>(cols));

    // read grid from stdin
    char curr {};
    for (int row: std::ranges::views::iota(0, rows))
    {
        for (int col: std::ranges::views::iota(0, cols))
        {
            std::cin >> curr;
            grid.at(row).at(col) = curr;
        }
    }


    if (dfs(grid, 0, 0) != FOUND)
    {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    // print
    for (int row: std::ranges::views::iota(0, rows))
    {
        for (int col: std::ranges::views::iota(0, cols))
        {
            std::cout << grid.at(row).at(col);
        }
        std::cout << "\n";
    }
    return 0;
}