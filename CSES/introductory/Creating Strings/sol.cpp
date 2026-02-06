#include <bits/stdc++.h>

const int ALPHA_LEN { 26 };
const int FIRST_ALPHA_CHAR { (int)'a' };

int ctoi(char c)
{
    // constraints guarantee only a-z input
    return (int)c - FIRST_ALPHA_CHAR;
}

char itoc(int i)
{
    return (char)(i + FIRST_ALPHA_CHAR);
}

// binomial coefficient
int nCr(int n, int r)
{
    int res { 1 };
    for (int i {n}; i > r; --i) {
        res *= i;
    }
    for (int i {n - r}; i > 1; --i) res /= i;

    return res;
}

int main()
{
    std::string s;
    std::cin >> s;

    // string only contains a-z, array is better than a map
    std::array<int, ALPHA_LEN> frequencies {};
    for (char c : s) frequencies.at(ctoi(c)) += 1;


    // number of unique permutations of s is the number of spaces available choose frequency of each character, decreasing the spaces
    // available by the frequency, can also construct lexographically first permutation here
    // we would use a vector and compute this with size, but precomputing possibilities saves time and space
    int replace_index { 0 };
    int possibilities { 1 };
    int remaining_spaces { (int)s.length() }; // guaranteed length <= 8

    // no longer need s, can use it to store lexographically first permutation
    for (int i {0}; i < ALPHA_LEN; ++i)
    {
        s.replace(replace_index, frequencies.at(i), frequencies.at(i), itoc(i));
        replace_index += frequencies.at(i);
        possibilities *= nCr(remaining_spaces, frequencies.at(i));
        remaining_spaces -= frequencies.at(i);
    }

    std::cout << possibilities << "\n";


    for (; possibilities > 0; --possibilities)
    {
        std::cout << s << "\n"; 
        std::next_permutation(s.begin(), s.end());
    }

    return 0;
}