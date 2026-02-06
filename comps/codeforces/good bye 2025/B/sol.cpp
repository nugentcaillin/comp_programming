#include <bits/stdc++.h>

int main()
{
    int t {};
    std::cin >> t;

    for ([[maybe_unused]] int _ : std::ranges::views::iota(0, t))
    {
        std::string s;
        std::cin >> s;

        // end chars must be s due to u rule, guarantees at least 2 s
        int ops { 0 };
        if (s.at(0) == 'u') ++ops;
        s.at(0) = 's';

        if (s.at(s.length() - 1) == 'u') ++ops;
        s.at(s.length() - 1) = 's';

        // u's may never appear next to each other, when two next to eachother, must convert one into s, choosing second one is guaranteed to not take more ops than first, and could take less

        for (int i { 1 }; i < s.length(); ++i)
        {
            if (s.at(i) == 'u' && s.at(i-1) == 'u')
            {
                ++ops;
                s.at(i) = 's';
            }
        }

        std::cout << ops << "\n";

    }
    return 0;
}