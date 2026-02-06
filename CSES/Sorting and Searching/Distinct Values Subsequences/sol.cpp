#include <map>
#include <iostream>
#include <ranges>

// each number appears in a distinct subsequence 0 or 1 times, 
// so, if a number appears x times, for any given subsequence it appears 0 times or it is selected from any position it is found in the array
// meaning each value added makes freq + 1 times more possibilities for subsequences

const int MOD { 1000000007 };

int main()
{
    int n {};
    std::cin >> n;

    std::map<int, int> frequencies {};

    for ([[maybe_unused]] int _ : std::ranges::views::iota(0, n))
    {
        int curr {};
        std::cin >> curr;
        frequencies[curr] += 1;
    }

    long long ways { 1 }; // 1 way to select empty set

    for (auto [val, freq] : frequencies)
    {
        // can choose each val freq + 1 ways, since we could not include it in any subsequence or select from any index it appears in
        ways *= ((freq + 1) % MOD);
        ways %= MOD;
    }

    // remove empty set
    --ways;

    std::cout << ways << "\n";

    return 0;
} 
