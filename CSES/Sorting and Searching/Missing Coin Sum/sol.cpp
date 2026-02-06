#include <bits/stdc++.h>

int main()
{
    // the minimum sum we cannot make is 1 greater than some sum we can make from the set of coins C

    // supose we start with a set S representing the minimum sum we cannot make, containing only the number one. We 
    // then choose a coin C to move to S, and if a subset of C cannot sum to the sum of S, S is a sum that cannot 
    // be reached by a subset of C. 
    //
    // if C does not contain a 1 at the start, this sum is 1
    // if it does, any valid S must contain that 1 from C.
    //
    // So, consider a sorted list of elements from C. At each step, add the minimum element in C to S,
    // as long as the new minimum of C is <= to the sum of elements in S, this sum can be reached,
    // continue until min > sum of S
    
    size_t n {};
    std::cin >> n;
    std::vector<int> coins;
    coins.reserve(n);

    for ([[maybe_unused]] size_t _ : std::ranges::views::iota((size_t)0, n))
    {
        int curr {};
        std::cin >> curr;
        coins.push_back(curr);
    }
    std::sort(coins.begin(), coins.end());

    // 1 + 2 + ... + 10^5 is a possible sum and would overflow int
    long long min_sum { 1 };
    auto min_not_chosen { coins.begin() };
    while (min_not_chosen != coins.end() &&  *min_not_chosen <= min_sum)
    {
        min_sum += *min_not_chosen;
        ++min_not_chosen;
    }
    std::cout << min_sum << "\n";
}