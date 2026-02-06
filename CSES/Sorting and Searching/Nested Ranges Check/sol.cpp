#include <vector>
#include <utility>
#include <iostream>
#include <ranges>
#include <algorithm>

// say we have a sorted list of ranges,
// a range contains another iff it has a range that starts after it and finishes before it 

int main()
{
    int n {};
    std::cin >> n;

    std::vector<std::tuple<int, int, int>> ranges; // start, stop, index for print
    std::vector<std::pair<bool, bool>> containment(n); // contains, is contained

    ranges.reserve(n);

    // keep track of points in order, and get sorted list of start and finish points

    for (int print_index : std::ranges::views::iota(0, n))
    {
        int start {};
        int finish {};
        std::cin >> start >> finish;
        ranges.push_back({start, finish, print_index});
    }

    std::sort(ranges.begin(), ranges.end());

    for (int i : std::ranges::views::iota(0, n))
    {
        auto [start, finish, print_index] = ranges.at(i);

        // check all ranges that start after current, but finish before for containment
        for (int j { i + 1 }; j < n && std::get<0>(ranges.at(j)) < finish; ++j)
        {
            auto [later_start, later_finish, later_print_index] = ranges.at(j);
            // check if range contains later range
            if (later_finish <= finish) {
                // update this and range that is contained
                auto [contains, is_contained] = containment.at(print_index);
                auto [later_contains, later_is_contained] = containment.at(later_print_index);
                containment.at(print_index) = { true, is_contained };
                containment.at(later_print_index) = { later_contains, true };

            }
        }


    }


    // print if contains other
    for (auto [contains, _] : containment)
    {
        std::cout << (int)contains << " ";
    }
    std::cout << "\n";

    // print if contained by other
    for (auto [_, is_contained] : containment)
    {
        std::cout << (int)is_contained << " ";
    }
    std::cout << "\n";


    return 0;
}

