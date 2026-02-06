#include <bits/stdc++.h>


int main()
{
    // maintain sorted list of arrivals and departures, can use a two pointer approach to maintain a running total of guests in restaurant

    int n {};
    std::vector<int> arrivals;
    std::vector<int> departures;

    std::cin >> n;

    arrivals.reserve(n);
    departures.reserve(n);

    for ([[maybe_unused]] int _ : std::ranges::views::iota(0, n))
    {
        int arrival {};
        int departure {};
        std::cin >> arrival >> departure;
        arrivals.push_back(arrival);
        departures.push_back(departure);
    }

    std::sort(arrivals.begin(), arrivals.end());
    std::sort(departures.begin(), departures.end());

    auto next_departure { departures.begin() };

    // inc count ant time for each arrival, then decrement until next departure is greater than current time
    int count { 0 };
    int max_count { 0 };
    for (int current_time : arrivals)
    {
        ++count;
        while (next_departure != departures.end() && *next_departure <= current_time) 
        {
            ++next_departure;
            --count;
        }

        max_count = std::max(count, max_count);
    }

    std::cout << max_count << "\n";

    return 0;
}