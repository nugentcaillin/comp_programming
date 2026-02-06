#include <bits/stdc++.h>

int main()
{
    const int ALPHA_LENGTH = 26;
    const char ALPHA_START = 'A';

    std::string palindrome;
    std::array<int, ALPHA_LENGTH> frequencies;
    frequencies.fill({0});
    std::cin >> palindrome;

    int odd_count { 0 };

    // a palindrome can be formed from s iff there is at most one character with odd frequency
    for (const char c: palindrome)
    {
        int index { c - (int)ALPHA_START }; // constraints guarantee s contains only A-Z
        frequencies.at(index) += 1;
        if (frequencies.at(index) % 2 == 0) --odd_count;
        else ++odd_count;
    }   

    if (odd_count > 1) 
    {
        std::cout << "NO SOLUTION\n";
        return 0;
    }

    // can form palindrome by adding half of each even freq char to start and end of unfilled portion of string, and odd in middle

    int unfilled_start_index { 0 };
    int unfilled_end_index { (int)palindrome.size() }; // constraints guarantee length <= 10^6
    int middle_index { (int)palindrome.size() / 2 }; // palindromes with an odd frequency character are always odd in length and have a middle character
    
    for (int i { 0 }; i < ALPHA_LENGTH; ++i)
    {
        char c { (char)(ALPHA_START + i) };
        int length { frequencies.at(i) };
        int half_length { length / 2 };

        if (frequencies.at(i) % 2 == 1)
        {
            // odd frequencies go in middle
            int starting_index { middle_index - half_length };
            palindrome.replace(starting_index, length, length, c);
            continue;
        }
        
        // even frequencies get added at start and end
        palindrome.replace(unfilled_start_index, half_length, half_length, c);
        unfilled_start_index += half_length;

        palindrome.replace(unfilled_end_index - half_length, half_length, half_length, c);
        unfilled_end_index -= half_length;
    }

    std::cout << palindrome << "\n";

    return 0; 
}