#include <vector>
#include <iostream>
#include <algorithm>
#include <ranges>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

// for being contained
// if we sort by start asc and then finish desc, when looking at them one by one, 
// the number of ranges containing current one is the number of finishes >= current finish seen so far
// and for containment if we sort by finish asc and start desc, number of ranges contained is number seen so far with start >= current start 

// can find number less than value efficiently with an order statistics tree with a custom comparator for duplicates

struct CustomComparator
{
    bool operator()(int a, int b) const
    {
        // we want duplicates to be added
        return a <= b;
    }
};


typedef tree<int, null_type, CustomComparator, rb_tree_tag, tree_order_statistics_node_update> indexed_set;

int main()
{
    int n {};
    std::cin >> n;

    std::vector<std::tuple<int, int, int>> ranges; // start, stop, index for print

    // separate vectors for 
    std::vector<int> contains_other(n);
    std::vector<int> is_contained(n);

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

    indexed_set stops_seen_so_far {};
    // check how many ranges contain each range
    for (auto [_, stop, print_index] : ranges)
    {
        // number that contain this range is equal to the number of ranges seen so far with stop >= this
        int number_containing = stops_seen_so_far.size() - stops_seen_so_far.order_of_key(stop);
        is_contained.at(print_index) = number_containing;
        stops_seen_so_far.insert(stop);
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

    // check how many ranges are contained
    indexed_set starts_seen_so_far {};
    for (auto [start, _, print_index] : ranges)
    {
        // number that this range contains is equal to the number of starts seen >= this start
        int number_contained = starts_seen_so_far.size() - starts_seen_so_far.order_of_key(start);
        contains_other.at(print_index) = number_contained;
        starts_seen_so_far.insert(start);
    }


    // print results
    for (int num_contained : contains_other)
    {
        std::cout << num_contained << " ";
    }
    std::cout << "\n";
    for (int num_contains : is_contained)
    {
        std::cout << num_contains << " ";
    }
    std::cout << "\n";

    return 0;
}