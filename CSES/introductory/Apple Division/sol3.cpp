#include <bits/stdc++.h>



int main()
{
    int n {};
    std::cin >> n;

    std::vector<int> nums;
    nums.reserve(n);

    long long sum {0};

    // get all numbers and compute sum
    for (int i {1}; i <= n; ++i)
    {
        int num {};
        std::cin >> num;
        nums.push_back(num);
        sum += num;
    }

    long long min_diff { sum };
    // n is small, brute force is feasable
    // consider every number 0 through 2^n - 1, // let each bit indicate prescence or absence in a group

    for (int i {0}; i < (1 << n); ++i)
    {
        std::vector<int> c;
        int bitmask { i };
        long long diff {0};
        for (int j {0}; j < n; ++j)
        {
            if (bitmask % 2 == 1) 
            {
                diff += nums.at(j);
            }
            else {
                diff -= nums.at(j);
            }
            bitmask >>= 1;
        }
        if (std::abs(diff) < min_diff) {
            min_diff = std::abs(diff);
        }
    }
    std::cout << min_diff << "\n";

    return 0;
}