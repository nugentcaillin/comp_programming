// for each index, we know the sum we need to make with two remaining indexes to make x. Can then use two pointer approach
// on sorted list skipping current val

#include <vector>
#include <utility>
#include <ranges>
#include <iostream>
#include <algorithm>

// two pointer approach to see if needed sum can be found using remaining two slots
bool find_match(std::vector<std::pair<int, int>>& vals, int needed_sum, int chosen_index, int& second_index, int& third_index)
{
    int lo {};
    int hi = vals.size() - 1;
    while (lo < hi) 
    {
        auto [lo_val, lo_index] = vals.at(lo);
        auto [hi_val, hi_index] = vals.at(hi);
        if (lo_index == chosen_index) 
        {
            ++lo;
            continue;
        }
        if (hi_index == chosen_index)
        {
            --hi;
            continue;
        }
        if (lo_val + hi_val > needed_sum) 
        {
            --hi;
            continue;
        }
        if (lo_val + hi_val < needed_sum)
        {
            ++lo;
            continue;
        }
        // sum found
        second_index = lo_index;
        third_index = hi_index;
        return true;
    }
    return false;
} 


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n {}; int target_sum {};
    std::cin >> n >> target_sum;


    std::vector<std::pair<int, int>> vals {};
    vals.reserve(n);

    
    for (int original_index : std::ranges::views::iota(1, n + 1))
    {
        int curr {};
        std::cin >> curr;
        vals.push_back({ curr, original_index });
    }



    std::sort(vals.begin(), vals.end());

    bool match_found {};
    int second_index {}; int third_index {};

    // for each element, assume is part of three chosen, calculate needed sum from other two and see if can be formed
    for (auto [ val, original_index ] : vals)
    {
        int needed_sum { target_sum - val };
        if (needed_sum < 2) continue;
        match_found = find_match(vals, needed_sum, original_index, second_index, third_index);
        if (match_found)
        {
            std::cout << original_index << " " << second_index << " " << third_index << "\n";
            break;
        }
    }

    if (!match_found) std::cout << "IMPOSSIBLE\n";

    return 0;
}