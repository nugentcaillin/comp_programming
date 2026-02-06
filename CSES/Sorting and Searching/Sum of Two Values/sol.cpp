#include <bits/stdc++.h>

int main()
{
    // sort and two pointer approach to find sum, since we need 1 indexed positions rather than elements, store elements as <value, initial pos> pairs
    // and algorithm works identically - we do not care about relative position of equal elements so standard pair operator< is fine for sort

    int n {}; int target {};
    std::cin >> n >> target;
    // <val, pos>
    std::vector<std::pair<int, int>> nums {};
    nums.reserve(n);

    for (int pos : std::ranges::views::iota(1, n+1))
    {
        int val {};
        std::cin >> val;
        nums.push_back({ val, pos });
    }

    std::sort(nums.begin(), nums.end());
    // two pointer to find sum
    auto left { nums.begin() }; auto right { --nums.end() };

    while (left != right)
    {
        auto [small, _] = *left;
        auto [big, _2] = *right; // c++26 placeholders cannot be used :(

        if (big + small > target)
        {
            // if big + small is larger than target, big must be decreased
            --right;

        } else if (big + small < target)
        {
            // if big + small is smaller than target, small must be increased
            ++left;
        } else break; // solution found
    }

    if (left == right)
    {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    auto [_, left_index] = *left;
    auto [_2, right_index] = *right;

    std::cout << left_index << " " << right_index << "\n";

    return 0;
}