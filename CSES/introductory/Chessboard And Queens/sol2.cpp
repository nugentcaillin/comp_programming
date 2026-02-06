#include <bits/stdc++.h>


// 8x8 board, 64C8 ways to place 8 queens
// ~= 10^9 ways, brute force possible if we can make the solution space smaller

// each queen prevents another queen from being placed in that row and column
// - ignoring diagonals, after placing a queen there are 8 - n rows and 8 - n columns available
// 8!, brute force can work 

const int BOARD_SIZE { 8 };


int main()
{


    std::array<std::array<bool, BOARD_SIZE>, BOARD_SIZE> can_place {};

    for (int row { 0 }; row < BOARD_SIZE; ++row)
    {
        for (int col { 0 }; col < BOARD_SIZE; ++col)
        {
            char c {};
            std::cin >> c;
            // . indicates free space
            can_place.at(row).at(col) = c == '.';
        }
    }


    // if there are n available spaces, you can place 1 queen n times


    // let cols[i] dictate the col that each queen placed in row i occupies
    auto r = std::ranges::views::iota(0, BOARD_SIZE);
    std::vector<int> cols(r.begin(), r.end());


    int ways { 0 };

    // check each permutation for rows queens could occupy for validity
    do 
    {
        bool valid { true };

        // if we have a queen placed in a non-free space, invalid
        for (int row {0}; row < BOARD_SIZE; ++row)
        {
            if (!can_place.at(row).at(cols.at(row)))
            {
                valid = false;
                break;
            }


        } 
        if (!valid) continue;


        // check for diagonality, a queen sees another queen if their horizontal and vertical distance
        // are of equal magnitude
        for (int row_1 {0}; row_1 < BOARD_SIZE; ++ row_1)
        {
            for (int row_2 { row_1 + 1 }; row_2 < BOARD_SIZE; ++ row_2)
            {
                int col_1 { cols.at(row_1) };
                int col_2 { cols.at(row_2) };

                int vertical_distance { std::abs(row_1 - row_2) };
                int horizont_distance { std::abs(col_1 - col_2) };
                
                if (vertical_distance == horizont_distance) 
                {
                    valid = false;
                    break;
                }
            }
            if (!valid) break;       
        }


        if (valid) ++ways;

    } while (std::next_permutation(cols.begin(), cols.end()));


    std::cout << ways << "\n";
}