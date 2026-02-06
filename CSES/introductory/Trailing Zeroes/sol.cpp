#include <bits/stdc++.h>

int main()
{
    long long n {};
    std::cin >> n;

    // for a trailing zero to be created, there needs to be a factor, or combination of factors that forms a multiple of 10
    // 10 is composed of 2 and 5, so the number of trailing zeroes will be the min(multiples of 2, multiples of 5)
    // for a factorial, 5 will be the limiting factor, so number of trailing zeroes is the number of factors of 5 n! has
    // this is equal to the sum of the number of times each power of 5 divides n
    long long count {0};
    for (int factor {5}; factor <= n; factor *= 5)
    {
        count += n / factor;
    }
    std::cout << count << "\n";

    return 0;
}