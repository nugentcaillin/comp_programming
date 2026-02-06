#include <bits/stdc++.h>

int main()
{
    int n {}; int curr {}; int max {0};
    std::cin >> n;

    std::vector<int> nums {};
    nums.reserve(n);


    for (int i {0}; i < n - 1; ++i) {
        std::cin >> curr;
        nums.push_back(curr);
        max = std::max(max, curr);
    }
    nums.push_back(max); // extra of largest does not mess with sort order and ensures correctness if largest num is one missing

    std::sort(nums.begin(), nums.end(), std::less<int>{});

    for (int i { 1 }; i <= n; ++i) {
        if (nums.at(i - 1) != i) {
            std::cout << i << "\n";
            break;
        }
    }
    
    return 0;
}