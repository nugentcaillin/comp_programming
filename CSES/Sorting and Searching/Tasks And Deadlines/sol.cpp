#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <utility>
#include <numeric>

// every task has reward d if it is finished at time zero,
// this reward becomes one less until deadline for all tasks

// we want to maximize d - f
// greedy approach - at each step choose task that finishing now gives maximum score 
// score is deadline - finish time
// or deadline - (current time + duration) == deadline - curent time - duration

// consider two tasks, each has a duration du_1, 2, and a deadline (d1, d2)
// the reward for taking these two tasks, with 1 being first task, and 2 being second task at time c
// is (de_1 - c - du_1) + (de_2 - (c + du_1) - du_2)
// or, simplified is de_1 + de_2 -2c - 2du_1 - du_2 
// as we can see, due to the advancement of time, the duration of the 1st task contributes double to the reduction of score, as it both takes away points
// from the first task as we do it, and makes the second start later.
// So, we are guaranteed to find the optimal solution if we do tasks sorted by duration ascending

int main()
{
    int n {};
    std::cin >> n;

    std::vector<std::pair<int, int>> tasks;
    tasks.reserve(n);

    for ([[maybe_unused]] int _ : std::ranges::views::iota(0, n))
    {
        int duration {};
        int deadline {};
        std::cin >> duration >> deadline;
        tasks.push_back({ duration, deadline });
    }

    std::sort(tasks.begin(), tasks.end(), std::less<std::pair<int, int>>());

    long long current_time {};
    long long score {};
    for (auto [duration, deadline] : tasks)
    {
        current_time += duration;
        score += deadline;
        score -= current_time;
    }


    std::cout << score << "\n";

    return 0;
}
