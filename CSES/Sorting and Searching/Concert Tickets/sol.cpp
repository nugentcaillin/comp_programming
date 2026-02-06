#include <bits/stdc++.h>

const int NOT_FOUND { -1 };

int main()
{
    // maintain sorted list of prices, binary search to find first <= preference, remove from list
    int num_tickets {};
    int num_customers {};
    std::cin >> num_tickets >> num_customers;

    std::map<int, int> prices {};
    std::vector<bool> taken(num_tickets, false);
    // prices.reserve(num_tickets);

    for ([[maybe_unused]] int _ : std::ranges::views::iota(0, num_tickets))
    {
        int price {};
        std::cin >> price;
        prices[price] += 1;
    }

    // std::sort(prices.begin(), prices.end());

    for ([[maybe_unused]] int _ : std::ranges::views::iota(0, num_customers))
    {
        int pref {};
        std::cin >> pref;
        
        auto first_greater { prices.upper_bound(pref) };

        if (first_greater == prices.begin())
        {
            std::cout << NOT_FOUND << "\n";
            continue;
        }
        auto chosen_ticket { std::prev(first_greater, 1) };
        std::cout << chosen_ticket->first << "\n";
        chosen_ticket->second = chosen_ticket->second - 1;
        if (chosen_ticket->second == 0) prices.erase(chosen_ticket);


    }
    return 0;

}