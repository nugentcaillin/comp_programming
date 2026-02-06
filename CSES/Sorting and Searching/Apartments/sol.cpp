#include <bits/stdc++.h>

int main()
{
    int applicant_count {};
    int appartment_count {};
    int max_diff {};

    std::cin >> applicant_count >> appartment_count >> max_diff;

    std::vector<int> applicant_preferences {};
    applicant_preferences.reserve(applicant_count);

    std::vector<int> appartment_sizes {};
    appartment_sizes.reserve(appartment_count);

    for (int i : std::ranges::views::iota(0, applicant_count))
    {
        int curr {};
        std::cin >> curr;
        applicant_preferences.push_back(curr);
    }
    for (int i: std::ranges::views::iota(0, appartment_count))
    {
        int curr {};
        std::cin >> curr;
        appartment_sizes.push_back(curr);
    }

    // there will be no applicant that will accept an appartment smaller than the applicant with smallest preferences -
    // can take a greedy sorting approach 
    // sort applicants and appartments, assign each applicant in order to the smallest appartment they will accept that 
    // is not yet assigned

    std::sort(applicant_preferences.begin(), applicant_preferences.end());
    std::sort(appartment_sizes.begin(), appartment_sizes.end());


    auto curr_appartment { appartment_sizes.begin() };
    int count { 0 };

    for (int pref : applicant_preferences)
    {
        // if the current appartment is too small for this applicant, no applicant following will accept it as all after have preferences >= this
        while (curr_appartment != appartment_sizes.end() &&  *curr_appartment + max_diff < pref)
        {
            ++curr_appartment;
        }

        if (curr_appartment == appartment_sizes.end()) break; // no applicant not yet looked at will accept an appartment smaller than the current one

        if (std::abs(*curr_appartment - pref ) <= max_diff)
        {
            ++count;
            ++curr_appartment; // this appartment now assigned - cannot be claimed
        }
    }

    std::cout << count << "\n";

    return 0;
}