#include <bits/stdc++.h>

const int ROWS { 8 };
const int COLS { 8 };
const int QUEENS { 8 };


int ways_to_place(std::array<std::array<bool, COLS>, ROWS> can_place, int queens_to_place, std::array<std::array<bool, COLS>, ROWS> have_checked)
{
    int ways { 0 };

    // if one queen, ways is available spaces
    if (queens_to_place == 1)
    {
        for (std::array<bool, COLS> row: can_place)
        {
            for (bool cell_free : row)
            {
                if (cell_free) ++ways;
            }
        }
        return ways;
    }

    // otherwise, place queen, block out non available cells and then find n - 1
    for (int row : std::ranges::views::iota(0, ROWS))
    {
        for (int col : std::ranges::views::iota(0, COLS))
        {
            if (have_checked.at(row).at(col)) continue;
            if (can_place.at(row).at(col))
            {
                have_checked.at(row).at(col) = true;
                // duplicate can_place and mark attacked squares as taken
                std::array<std::array<bool, COLS>, ROWS> new_can_place = can_place;
                new_can_place.at(row).at(col) = false;
                // mark any horizontal, vertical or diagonal as taken
                bool in_bounds { true };
                int offset { 1 };
                while (in_bounds)
                {
                    in_bounds = false;

                    // horizontal
                    if (row + offset < ROWS)
                    {
                        in_bounds = true;
                        new_can_place.at(row+offset).at(col) = false;
                    }
                    if (row - offset >= 0)
                    {
                        in_bounds = true;
                        new_can_place.at(row-offset).at(col) = false;
                    }

                    // vertical
                    if (col + offset < COLS)
                    {
                        in_bounds = true;
                        new_can_place.at(row).at(col+offset) = false;
                    }
                    if (col - offset >= 0)
                    {
                        in_bounds = true;
                        new_can_place.at(row).at(col-offset) = false;
                    }

                    // diagonal
                    if (col + offset < COLS && row + offset < ROWS)
                    {
                        in_bounds = true;
                        new_can_place.at(row+offset).at(col+offset) = false;
                    }
                    if (col + offset < COLS && row - offset >= 0)
                    {
                        in_bounds = true;
                        new_can_place.at(row-offset).at(col+offset) = false;
                    }
                    if (col - offset >= 0 && row + offset < ROWS)
                    {
                        in_bounds = true;
                        new_can_place.at(row+offset).at(col-offset) = false;
                    }
                    if (col - offset >= 0 && row - offset >= 0)
                    {
                        in_bounds = true;
                        new_can_place.at(row-offset).at(col-offset) = false;
                    }
                    ++offset;
                }

                ways += ways_to_place(new_can_place, queens_to_place - 1, have_checked);
            }
        }
    }
    return ways;
}


int main()
{
    std::array<std::array<bool, COLS>, ROWS> can_place {};
    std::array<std::array<bool, COLS>, ROWS> have_checked {};

    for (int row { 0 }; row < ROWS; ++row)
    {
        for (int col { 0 }; col < COLS; ++col)
        {
            char c {};
            std::cin >> c;
            // . indicates free space
            can_place.at(row).at(col) = c == '.';
        }
    }


    // if there are n available spaces, you can place 1 queen n times

    // the number of ways that we can place n queens on a board, is the number of ways
    // we can place n - 1 queens on the available spaces after each possible placement of a queen

    int ways { ways_to_place(can_place, QUEENS, have_checked) };
    std::cout << ways << "\n";

    return 0;
}