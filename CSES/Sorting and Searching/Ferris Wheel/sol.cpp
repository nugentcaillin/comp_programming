#include <bits/stdc++.h>


int main()
{
    int num_children {};
    int max_weight {};

    std::cin >> num_children >> max_weight;
    std::vector<int> weights {};
    weights.reserve(num_children);

    for ([[maybe_unused]]int _: std::ranges::views::iota(0, num_children))
    {
        int curr {};
        std::cin >> curr;
        weights.push_back(curr);
    }

    int gondolas { 0 };

    // can take a greedy, sorting, two pointer approach - there does not exist a better pairing than putting heaviest child with lightest child, or by itself
    // if lightest cannot fit. Sort weights, use pointer for lightest and heaviest, for each heaviest child, put in carousel, then add lightest child
    // not yet placed if they fit

    std::sort(weights.begin(), weights.end());
    auto lightest_unassigned { weights.begin() };
    auto heaviest_unassigned { --weights.end() };


    while (heaviest_unassigned >= lightest_unassigned)
    {
        ++gondolas;

        // lightest only put in gondola if they fit, heaviest always put in gondola
        if (*lightest_unassigned + *heaviest_unassigned <= max_weight) ++lightest_unassigned;
        --heaviest_unassigned;
    }

    std::cout << gondolas << "\n";

    return 0;
}