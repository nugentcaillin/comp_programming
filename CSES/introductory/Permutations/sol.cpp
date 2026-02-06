#include <bits/stdc++.h>

int main()
{
    int n {};
    std::cin >> n;

    // we can construct any beautiful permutations using only even or odd numbers
    // so, if we have any pair of odd, even number such that they are more than 2 apart we can construct one
    // any n > 3 has a beautiful permutation, also 1
    // one construction is all odd numbers followed by all even numbers e.g. 2 4 6 8 1 3 5 7 9

    if (n == 1)
    {
        std::cout << "1\n";
        return 0;
    }

    if (n <= 3) 
    {
        std::cout << "NO SOLUTION\n";
        return 0;
    }
    
    // evens
    for (int i { 2 }; i <= n; i += 2) std::cout << i << " ";
    for (int i { 1 }; i <= n; i += 2) std::cout << i << " ";
    std::cout << "\n";

    return 0;
}