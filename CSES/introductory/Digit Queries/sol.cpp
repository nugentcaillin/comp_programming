#include <bits/stdc++.h>

void solve()
{
    long long k {};
    std::cin >> k;

    long long num_length { 1 };
    long long numbers_of_length { 9 };
    long long next_index { 1 };


    // there are 9 numbers of length 1, 10* as many per digit of length, can skip indexes until we are at the right number length
    while (next_index + numbers_of_length * num_length <= k && next_index + numbers_of_length * num_length > 0) // need to account for overflow
    {
        next_index += numbers_of_length * num_length;
        num_length += 1;
        numbers_of_length *= 10;
    }


    // now that we have the number length that we get into, and the index this length of number starts at, can calculate how many numbers we pass with
    // integer division, and the digit of that last number needed with modulus
    long long digit_gap { k - next_index };
    long long number_gap { digit_gap / num_length };
    long long digit_index { digit_gap % num_length };

    long long next_number { 1 };

    // get smallest number that has right length, nth number of that lengfth is that number + n
    for (int i : std::ranges::views::iota(1, num_length)) next_number *= 10;
    next_number += number_gap;

    // get digit by dividing by 10 until relevant digit is last
    for (int i : std::ranges::views::iota(1, num_length - digit_index)) next_number /= 10;

    int digit { (int)(next_number % 10) };
    std::cout << digit << "\n";
}


int main()
{
    int q {};
    std::cin >> q;

    for (int i : std::ranges::views::iota(0, q)) solve();
}