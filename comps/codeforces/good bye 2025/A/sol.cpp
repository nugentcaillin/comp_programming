#include <bits/stdc++.h>

int main()
{
    // we can combine NN to N, NY or YN to Y, and cannot combine YY
    // can reduce to one character iff there is <= 1 Y

    int t {};
    std::cin >> t;

    for ([[maybe_unused]] int _ : std::ranges::views::iota(0, t))
    {
        std::string s {};
        std::cin >> s;

        int count_y { 0 };

        for (char c : s)
        {
            if (c == 'Y') ++count_y;
        }
        if (count_y > 1) std::cout << "NO\n";
        else std::cout << "YES\n";
    }
    return 0;
}