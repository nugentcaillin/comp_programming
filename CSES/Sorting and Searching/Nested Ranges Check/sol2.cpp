#include <vector>
#include <iostream>
#include <algorithm>
#include <ranges>

// intuition: insertion of sorted tuples into binary tree by non sorted key gives answer

// consider checking whether a range is contained

// say we treat each range as a tuple (start, finish) and we sort this range by start

// now, we look at each finish time one by one in sorted order. If this finish point is not the largest one that we have encountered so far,
// since every range seen so far necessarily has a start <= current start, there exists a range that both starts before and finishes after
// and the number of ranges that contains it is the number of finish times >= current one, since we only care about existence and not number
// no need to maintain a tree, just largest encountered is fine

// for duplicates, if we have duplicate starts, we want the one with a larger finish to be seen first


// for containing others we can apply similar logic:
// we sort by stop point in ascending order, then look at ranges one by one,
// keeping track of largest start seen so far
// if the current start <= largest start seen, there similarly exists some range that starts after this one and finishes before it

// for duplicate ends we want largest start to be seen first

int main()
{
    int n {};
    std::cin >> n;

    std::vector<std::tuple<int, int, int>> ranges; // start, stop, index for print

    // separate vectors for 
    std::vector<bool> contains_other(n);
    std::vector<bool> is_contained(n);

    ranges.reserve(n);


    for (int print_index : std::ranges::views::iota(0, n))
    {
        int start {};
        int finish {};
        std::cin >> start >> finish;
        ranges.push_back({start, finish, print_index});
    }

    // work out if ranges are contained 

    // sort first with ascending start then descending finish
    std::sort(ranges.begin(), ranges.end(), [](std::tuple<int, int, int> first, std::tuple<int, int, int> second) {
        auto [start_first, stop_first, _first] = first; // can't use placeholders for print index because same scope and c++26 not allowed
        auto [start_second, stop_second, _second] = second;

        if (start_first < start_second) return true;
        if (start_first > start_second) return false;
        return stop_first > stop_second; 
        // guaranteed to not have start and stop identical from problem statement, don't need to factor third tuple argument
    });

    // check if each range has been contained by another
    int max_stop_seen {}; // smallest stop possible is 1
    for (auto [_, stop, print_index] : ranges)
    {
        if (stop <= max_stop_seen) is_contained.at(print_index) = true;
        max_stop_seen = std::max(max_stop_seen, stop);
    }


    // work out if ranges contain other ranges

    // sort first with ascending finish then descending start
    std::sort(ranges.begin(), ranges.end(), [](std::tuple<int, int, int> first, std::tuple<int, int, int> second) {
        auto [start_first, stop_first, _first] = first; // can't use placeholders for print index because same scope and c++26 not allowed
        auto [start_second, stop_second, _second] = second;

        if (stop_first < stop_second) return true;
        if (stop_first > stop_second) return false;
        return start_first > start_second;
        // guaranteed to not have start and stop identical from problem statement, don't need to factor third tuple argument
    });


    // check if each range contains another
    int max_start_seen {}; // smallest start possible is 1
    for (auto [start, _, print_index] : ranges)
    {
        if (start <= max_start_seen) contains_other.at(print_index) = true;
        max_start_seen = std::max(max_start_seen, start);
    }


    // print results
    for (bool b : contains_other)
    {
        std::cout << (int)b << " ";
    }
    std::cout << "\n";
    for (bool b : is_contained)
    {
        std::cout << (int)b << " ";
    }
    std::cout << "\n";

    return 0;
}