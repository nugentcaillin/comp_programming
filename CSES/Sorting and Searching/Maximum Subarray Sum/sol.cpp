#include <bits/stdc++.h>

int main()
{
    size_t n {};
    std::cin >> n;

    std::vector<int> nums {};
    nums.reserve(n);

    for ([[maybe_unused]] size_t _ : std::ranges::views::iota((size_t)0, n))
    {
        int curr {};
        std::cin >> curr;
        nums.push_back(curr);
    }

    // the maximum subarray ending at index i of array A will either be Ai + max subarray ending at i - 1 or Ai
    // since our only choice is to include or exclude previous element, and the max subarray ending at that element will
    // be the largest value we could add to Ai

    // max subarray sum ending at index 0 is A0, 
    // 10^9 * 10^5 could overflow int
    long long sum { nums.at(0) };
    long long max_sum { nums.at(0) };

    for (int num : nums | std::ranges::views::drop(1))
    {
        // max sum ending at this index is either the value or the sum ending at previous index
        sum = std::max((long long)num, sum + num);
        max_sum = std::max(sum, max_sum);
    }

    std::cout << max_sum << "\n";
}