#include <bits/stdc++.h>

int main()
{
    int a {}; 
    int b {};
    int t {};
    std::cin >> t;
    for (int i {1}; i <= t; ++i)
    {
        std::cin >> a >> b;

        // each operation removes 3 coins so total amount must be divisible by 3
        // also, to remove one coin from a pile we must remove two from the other
        // so, if one pile is more than double the other we cannot do it,
        // otherwise there exists some order of operations to remove all coins
        if ((a + b) % 3 != 0 || std::min(a, b) * 2 < std::max(a, b)) std::cout << "NO\n";
        else std::cout << "YES\n";
    }
    return 0;
}