#include <bits/stdc++.h>

int main()
{
    int n {}; int curr {}; int min_val {}; long long moves {0};

    std::cin >> n >> min_val;
    --n; // since we're consuming one number for starting val

    for (; n > 0; --n)
    {
        std::cin >> curr;
        if (curr < min_val) moves += min_val - curr;
        else min_val = curr;
    }

    std::cout << moves << "\n";

    return 0;
}