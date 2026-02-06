#include <bits/stdc++.h>

void print_bits(int n, int bits)
{
    for (int i { bits - 1 }; i >= 0; --i)
    {
        if ((n >> i) % 2 == 0) std::cout << "0";
        else std::cout << "1";
    }
    std::cout << "\n";
}


int main()
{
    int n {};
    std::cin >> n;


    int upper_bound { 1 << n }; // guaranteed n <= 16 so int is fine

    std::vector<int> gray_code {};
    gray_code.reserve(upper_bound);
    
    // gray of 1 bits to start
    gray_code.push_back(0);
    print_bits(gray_code.back(), n);
    gray_code.push_back(1);
    print_bits(gray_code.back(), n);

    int next_addition_index { 1 };
    int base { 2 }; // power of two to serve as leading one


    // the gray code of n+1 can be created by adding 0 to the rear of the gray code of n,
    // then travelling in reverse adding 1 to rear,
    // can use already existing numbers as portion with leading zero, can traverse backwards over all generated numbers to get portion with leading one
    for (int i { 3 }; i <= upper_bound; ++i)
    {
        gray_code.push_back(base + gray_code.at(next_addition_index));
        print_bits(gray_code.back(), n);

        if (next_addition_index == 0)
        {
            next_addition_index = gray_code.size();
            base *= 2;
        }
        --next_addition_index;
    }

    return 0;
}