#include <bits/stdc++.h>

int main()
{
    std::string s;
    std::cin >> s;

    int curr { 1 }; int longest { 1 }; // shortest is at least 1
    
    char prev { s.at(0) };
    for (char c : s | std::views::drop(1))
    {
        if (c == prev) ++curr;
        else curr = 1;
        prev = c;
        longest = std::max(longest, curr);
    }
    
    std::cout << longest << "\n";
    return 0;
}