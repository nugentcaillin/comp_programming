#include <bits/stdc++.h>
int main()
{
    // consider a sorted list, it will take 1 pass.
    // a number is moved such that it comes before its predecessor, it adds one pass, and this number now occurs before its immediate predecessor.
    // so, the number of passes it takes is 1 plus the number of elements such that the element occurs before its immediate predecessor
    // or, the number of elements such that their immediate successor has already been fount, can use a 'hash'

    size_t n {};
    std::cin >> n;
    std::vector<int> nums {};

    int passes { 1 };

    // since we are guaranteed to see every number 1 to n, vector is better than unordered_set
    // n + 2 for 1 based indexing, making sure we have space to index n + 1
    std::vector<bool> successors(n + 2, false);

    for (size_t _ : std::ranges::views::iota((size_t)0, n))
    {
        int curr {};
        std::cin >> curr;

        // if we have already encountered this number's immediate successor, must make one more pass to collect this number
        if (successors.at(curr + 1)) ++passes;
        successors.at(curr) = true;
    }

    std::cout << passes << "\n";

    return 0;
}