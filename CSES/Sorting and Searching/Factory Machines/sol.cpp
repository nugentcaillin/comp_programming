#include <iostream>
#include <ranges>
#include <vector>
#include <limits>


// want to find smallest time such that all machines can produce t products in that time
// worst case is using shortest machine k times

// can use binary search across machines, looking at each machine log n times - n log max num, ~= 10^18


long long binary_search(std::vector<int>& machines, long long lo, long long hi, int target)
{
    if (lo == hi) return hi;
    long long pivot = (hi + lo) / 2;

    long long sum_produced {};
    for (int machine : machines)
    {
        sum_produced += pivot / machine;
    }

    if (sum_produced >= target)
    {
        return binary_search(machines, lo, pivot, target);
    }
    return binary_search(machines, pivot + 1, hi, target);
}

int main ()
{
    int n {};
    int t {};
    std::cin >> n >> t;
    std::vector<int> machines {};
    machines.reserve(n);

    int min_machine {std::numeric_limits<int>::max()};
    for (int _ : std::ranges::views::iota(0, n))
    {
        int curr {};
        std::cin >> curr;
        machines.push_back(curr);
        min_machine = std::min(min_machine, curr);
    }

    long long worst_case = (long long)min_machine * t;
    long long min_time = binary_search(machines, 0, worst_case, t);
    std::cout << min_time << "\n";
}