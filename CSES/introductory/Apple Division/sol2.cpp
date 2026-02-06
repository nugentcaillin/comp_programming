#include <bits/stdc++.h>

int main()
{
    int n {};
    std::cin >> n;

    std::vector<int> nums {};

    int difference { 0 };

    for (int i {0}; i < n; ++i)
    {
        int curr {};
        std::cin >> curr;
        nums.push_back(curr);
        difference += curr;
    }


    // start with a set containing all the numbers,
    // remove the number that makes the difference closest to zero until none are remaining that can do so

    bool remaining_possibilities { true };

    while (remaining_possibilities)
    {
        std::cout << "curr: " << difference << "\n";
        remaining_possibilities = false;

        int best_index { 0 };
        int best_difference { difference };
        for (int i {0}; i < nums.size(); ++i)
        {
            int candidate_difference { difference - 2 * nums.at(i) };
            if (std::abs(candidate_difference) < std::abs(best_difference))
            {
                best_index = i;
                best_difference = candidate_difference;
                remaining_possibilities = true;
            }
        }

        if (!remaining_possibilities) break;
        difference = best_difference;
        std::swap(nums.at(best_index), nums.back());
        nums.pop_back();
    }

    std::cout << std::abs(difference) << "\n";
    return 0;

}