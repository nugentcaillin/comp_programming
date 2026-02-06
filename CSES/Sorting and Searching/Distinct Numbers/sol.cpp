#include <bits/stdc++.h>

int main()
{
    int n {};
    std::cin >> n;


    // for this input size, n log n of sort will be faster than n of hashing
    std::vector<int> nums {};
    nums.reserve(n);

    for (int i: std::ranges::views::iota(0, n))
    {
        int curr {};
        std::cin >> curr;
        nums.push_back(curr);
    }

    std::sort(nums.begin(), nums.end());

    // in sorted list, duplicates will appear next to each other -> unique numbers will be different from their preceeding number
    int count { 1 }; // first element always counted
    int prev { nums.at(0) };

    for (int num: nums | std::ranges::views::drop(1))
    {
        if (num != prev) ++count;
        prev = num;
    }


    std::cout << count << "\n";
}