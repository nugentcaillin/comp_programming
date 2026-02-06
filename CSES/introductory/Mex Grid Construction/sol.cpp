#include <bits/stdc++.h>

class MexGrid 
{
public:
    MexGrid(int n)
    : n_ {n}
    , grid_(n, std::vector<int>(n, 0))
    {
        // grid is mirrored along diagonal, place for upper diagonal and flip coordinates to get value for lower one
        // to cut down on the expensive-ish 2n operation to find min

        for (int row : std::ranges::views::iota(0, n))
        {
            for (int col : std::ranges::views::iota(0, n))
            {
                if (grid_.at(row).at(col) != 0) continue; // skip mirror image
                int val { get_min_not_placed(row, col) };
                grid_.at(row).at(col) = val;
                grid_.at(col).at(row) = val;
            }

            // values along diagonal are always zero, but no need to set since vector is already zeroed
        }
    }

    void print() const
    {
        for (const std::vector<int>& row: grid_)
        {
            for (int cell: row)
            {
                std::cout << cell << " ";
            }
            std::cout << "\n";
        }
    }

private:
    int n_;
    std::vector<std::vector<int>> grid_;

    bool not_placed_before_row(int row, int col, int val) const
    {
        bool not_found {true};
        for (int c: std::ranges::views::iota(0, col))
        {
            if (grid_.at(row).at(c) == val)
            {
                not_found = false;
                break;
            }
        }
        return not_found;
    }
    bool not_placed_before_col(int row, int col, int val) const
    {
        bool not_found {true};
        for (int r: std::ranges::views::iota(0, row))
        {
            if (grid_.at(r).at(col) == val) 
            {
                not_found = false;
                break;
            }
        }
        return not_found;
    }

    int get_min_not_placed(int row, int col) const 
    {
        // can have n - 1 to left and n - 1 above, so max a number could theoretically be is 2n - 1
        for (int curr : std::ranges::views::iota(0, n_ * 2))
        {
            if (not_placed_before_col(row, col, curr) && not_placed_before_row(row, col, curr)) return curr;
        }
        return -1;
    }

};

int main()
{
    int n {};
    std::cin >> n;
    MexGrid grid(n);
    grid.print();
    return 0;
}