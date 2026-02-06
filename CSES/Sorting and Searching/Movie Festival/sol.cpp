#include <bits/stdc++.h>

typedef int finish_t;
typedef int start_t;

// finish before start so we don't need a lambda for sort
typedef std::pair<finish_t, start_t> showing_t;

int main()
{
    // scheduling problem, greedy approach can work. Suppose we choose a movie A that starts at time t and finishes at time t + x.
    // if there exists a movie B that starts at time >= t and finishes at time < t + x, we are guaranteed that choosing B over A
    // will not decrease the total number of movies we can watch and may increase it
    
    // sort movies by finish time and start for movies with same finish time, ascending.
    // at each step, pick movie that finishes earliest that starts after current time

    int n {};
    std::cin >> n;

    std::vector<showing_t> showings {};
    showings.reserve(n);

    for ([[maybe_unused]] int _ : std::ranges::views::iota(0, n))
    {
        start_t start {}; finish_t finish;
        std::cin >> start >> finish;
        showings.push_back({finish, start});
    }

    std::sort(showings.begin(), showings.end());

    // we always pick showing that finishes earliest, count is always at least one
    auto [earliest_finish, _] = showings.front();
    int count { 1 };
    int curr_time { earliest_finish };

    for (auto [finish_time, start_time] : showings | std::ranges::views::drop(1))
    {
        // can only pick a movie if it is not interfered with by previous choice
        if (start_time < curr_time) continue;
        ++count;
        // we watch the chosen movie in its entirety and cannot pick more until it is finished
        curr_time = finish_time;
    }

    std::cout << count << "\n";
    return 0;
}