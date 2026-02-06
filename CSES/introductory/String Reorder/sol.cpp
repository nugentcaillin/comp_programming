#include <bits/stdc++.h>

const char ALPHA_START { 'A' };
const int ALPHA_LEN { 26 };

int ctoi(char c)
{
    return (int)c - (int)ALPHA_START;
}

char itoc(int i)
{
    return (char)(i + (int)ALPHA_START);
}

int main()
{
    std::string s {};
    std::cin >> s;
    
    // array is better than hash map with restriction of A-Z, hash chars as its zero indexed position in aplhabet
    std::array<int, ALPHA_LEN> hashmap {};

    // if any character is present more often than half the length rounded up, it is impossible to
    // not put two of these characters next to each other
    int max_frequency { (int)std::ceil((double)s.length() / 2) };

    for (char c : s)
    {
        hashmap.at(ctoi(c)) += 1;

        if (hashmap.at(ctoi(c)) > max_frequency)
        {
            std::cout << "-1\n";
            return 0;
        }
    }

    // at each position, we want to place the lexographically smallest character that does not prevent us from making
    // two adjacent characters different
    for (int place_index : std::ranges::views::iota(0, (int)s.length()))
    {  
        // if a character has frequency equal to half the length + 1, it must be the next character 
        int remaining_length { (int)s.length() - place_index };
        max_frequency = remaining_length / 2 + 1;
        bool max_found { false };
        
        for (int hash_index : std::ranges::views::iota(0, ALPHA_LEN))
        {
            if (hashmap.at(hash_index) != max_frequency) continue;
            if (place_index != 0 && itoc(hash_index) == s.at(place_index - 1)) continue;
            hashmap.at(hash_index) -= 1;
            s.at(place_index) = itoc(hash_index);
            max_found = true;
            break;
        }
        if (max_found) continue;

        // otherwise, choose lexographically smallest not equal to previous char
        for (int hash_index : std::ranges::views::iota(0, ALPHA_LEN))
        {
            if (hashmap.at(hash_index) == 0) continue;
            if (place_index != 0 && itoc(hash_index) == s.at(place_index - 1)) continue;
            hashmap.at(hash_index) -= 1;
            s.at(place_index) = itoc(hash_index);
            break;
        }
    
    }

    std::cout << s << "\n";

    return 0;
}