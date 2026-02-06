#include <bits/stdc++.h>

const int UNVISITED = -1;
const int KNIGHT_MOVES = 8;

typedef std::pair<int, int> coord_t;

class KnightGrid 
{
public:
    KnightGrid(int n)
    : grid_(n, std::vector<int>(n, UNVISITED))
    , n_(n)
    {
        // number of moves to get to top left from cell, is same as moves to get to that square from top left
        // - can perform BFS
        
        std::queue<coord_t> bfs;
        grid_.at(0).at(0) = 0;
        bfs.push({0, 0});
        while (!bfs.empty())
        {
            auto [row, col] = bfs.front();
            bfs.pop();

            // try all possible knight moves, and update if unvisited
            for (int move_index : std::ranges::views::iota(0, KNIGHT_MOVES))
            {
                int row_move { row_moves.at(move_index) };
                int col_move { col_moves.at(move_index) };
                int new_row { row + row_move };
                int new_col { col + col_move };

                bool valid_pos { new_row >= 0 && new_row < n_ && new_col >= 0 && new_col < n_};

                if (valid_pos && grid_.at(new_row).at(new_col) == UNVISITED)
                {
                    grid_.at(new_row).at(new_col) = grid_.at(row).at(col) + 1;
                    bfs.push({new_row, new_col});
                }
            }
        }
    }
    void print() const
    {
        for (std::vector<int> row : grid_)
        {
            for (int move_count : row)
            {
                std::cout << move_count << " ";
            }
            std::cout << "\n";
        }
    }
private:
    const std::array<int, KNIGHT_MOVES> row_moves {2, 2, -2, -2, 1, 1, -1, -1};
    const std::array<int, KNIGHT_MOVES> col_moves {1, -1, 1, -1, 2, -2, 2, -2};

    std::vector<std::vector<int>> grid_;
    int n_;
};


int main()
{
    int n {};
    std::cin >> n;
    KnightGrid grid {n};
    grid.print();
    return 0;
}