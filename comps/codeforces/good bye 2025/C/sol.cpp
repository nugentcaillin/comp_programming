#include <bits/stdc++.h>


long long max_X(int nice_index, int naughty_index, std::vector<int>& niceness)
{
    int nice { niceness.at(nice_index) };
    int naughty { niceness.at(naughty_index) };

    if (naughty_index == niceness.size() - 1)
    {
        return std::max(nice, -1 * naughty);
    }
    return std::max( nice + max_X(naughty_index, naughty_index + 1, niceness), -1 * naughty + max_X(nice_index, naughty_index + 1, niceness) );
}


int main()
{
    int t {};
    std::cin >> t;


    for ([[maybe_unused]] int _ : std::ranges::views::iota(0, t))
    {
        // std::vector<std::vector<int>> memo(250000, std::vector<int>(250000, -1));
        int child_count {};
        std::cin >> child_count;

        std::vector<int> niceness;
        niceness.reserve(child_count);
        for ([[maybe_unused]] int  _2 : std::ranges::views::iota(0, child_count))
        {
            int curr {};
            std::cin >> curr;
            niceness.push_back(curr);
        }

        std::cout << max_X(0, 1, niceness) << "\n";
    }
    return 0;
}