#include <bits/stdc++.h>

int main()
{
    long long n;
    int y {}; int x {}; // 1 indexed
    
    std::cin >> n;

    // now, if we know the value of the diagonal that the spiral number lines up with for its largest coordinate,
    // we can get the value instantly by subtracting/adding the difference in position depending on
    // if it is vertical or horizontal

    // each diagonal number takes two more squares to reach than the previous one, that is diagonal spiral 
    // numbers follow the sequence 1, 3, 7, 13 ...
    // so, if f(n) is the function that gives the nth diagonal number,
    // f(n) = f(n-1) + 2(n - 1) = f(n-1) + 2n - 2
    // f(1) = 1


    // now, 
    // f(1) = 1
    //
    // f(2) = f(1) + 2(2) - 2
    //
    // f(3) = f(2) + 3(2) - 2
    //      = f(1) + 2(2) - 2 + 3(2) - 2
    //
    // f(4) = f(3) + 4(2) - 2
    //      = f(1) + 2(2) - 2 + 3(2) - 2 + 4(2) - 2

    // now, we can collect like terms
    // f(3) = f(1) + 3(2) + 2(2) - 2 - 2
    // f(3) = f(1) + (3 + 2)(2) - (3-1)(2)
    //
    // f(4) = f(1) + (4 + 3 + 2)(2) - (4-1)(2)
    
    // this follows the pattern
    // f(n) = f(1) + (n + n - 1 + ... + 2)(2) - (n-1)(2)
    //      = f(1) + (1 + 2 + ... + n)(2) - 2n

    // sum of first n natural numbers has closed form so
    // f(n) = f(1) + n(1 + n) / 2 * 2 - 2n
    //      = 1 + n(1 + n) - 2n

    for (; n > 0; --n)
    {
        std::cin >> y >> x;
        long long largest { std::max(x, y) };
        int smallest { std::min(x, y) };


        int sign {};
        // every even horizontal increases right to left, every odd vertical increases bottom up from diagonal

        // travelling upward to get from diagonal to target
        if (smallest == y) sign = largest % 2 == 0 ? -1 : 1;
        // travelling right to left
        else sign = largest % 2 == 0 ? 1 : -1;

        // get relevant diagonal number
        long long diagonal { 1 + largest * (1 + largest) - 2 * largest };


        long long target { diagonal + sign * (largest - smallest) };
        std::cout << target << "\n";
    }
    return 0;
}