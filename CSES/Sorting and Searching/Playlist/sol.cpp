#include <bits/stdc++.h>

constexpr int LARGEST_NUM { 1000000000 };

int main()
{
    int n {};
    std::cin >> n;

    // longest sequence has no repeats inside of it -> can take a greedy approach, proceed forwards until we have one duplicate, 
    // then shrink from back until we have no duplicates
    
    // since we will have at most one element at any time that has freq 2, can use a bool vector to 'hash' numbers to whether they are present in current sequence
    // bool vector is reasonable for 10^9, but if number space was larger a hashset could be used
    // + 1 for one based indexing
    std::vector<bool> seen(LARGEST_NUM + 1, false);

    std::vector<int> nums {};
    nums.reserve(n);

    for (int _ : std::ranges::views::iota(0, n))
    {
        int curr {};
        std::cin >> curr;
        nums.push_back(curr);
    }

    auto lo { nums.begin() };
    auto hi { lo + 1 };
    seen.at(*lo) = true;

    int max_len { 0 };

    while (hi != nums.end())
    {
        int curr_len { (int)(hi - lo) }; // fine since n < 2 * 10^5
        max_len = std::max(curr_len, max_len);
        
        // if we would have a duplicate by increasing, shrink backwards until we would not
        while (seen.at(*hi))
        {
            seen.at(*lo) = false;
            ++lo;
        }

        seen.at(*hi) = true;
        ++hi;
    }

    // if longest occurs on last digit, need extra check
    int curr_len { (int)(hi - lo) }; // fine since n < 2 * 10^5
    max_len = std::max(curr_len, max_len);


    std::cout << max_len << "\n";
}