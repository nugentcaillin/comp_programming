#include <bits/stdc++.h>

int main()
{
    int n {};
    std::cin >> n;

    int mod { 1000000007 };
    // each additional bit gives 2x the possibility of bit strings

    int possibilities { 1 };

    for (; n >= 1; --n)
    {
        possibilities *= 2;
        possibilities %= mod;
    }

    std::cout << possibilities << "\n";
    return 0;
}