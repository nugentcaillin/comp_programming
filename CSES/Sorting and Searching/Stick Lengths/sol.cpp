#include <bits/stdc++.h>

int main()
{
    // say we have a 3 element array where 2 elements are equal and one is different, it will always be less expensive
    // to move the one element than the two equal ones, and the same distance would have to be moved.

    // greedy approach, sort lengths, have pointer to start and end, until pointers have same value, move pointers inwards till all
    // elements left/right are equal, then increment value at pointer with fewer elements to edge of array, and add cost
    // of incrementing all elements to edge of array to cost

    size_t n {};
    std::cin >> n;

    std::vector<int> lengths {};
    lengths.reserve(n);
    for (size_t _ : std::ranges::views::iota((size_t)0, n))
    {
        (void)_;
        int curr {};
        std::cin >> curr;
        lengths.push_back(curr);
    }

    // worst case is ~10^5 / 2 * 10^9, int will overflow
    long long cost {};

    std::sort(lengths.begin(), lengths.end());
    auto left { lengths.begin() };
    auto right { --lengths.end() };
    
    while (*left != *right)
    {
        // move until left and right are innermost element with all equal to outside of array
        while (left != lengths.end() - 1 && *left == *(left + 1)) ++left;
        while (right != lengths.begin() && *right == *(right - 1)) --right;

        long int left_distance { left - lengths.begin() + 1 };
        long int right_distance { lengths.end() - right };


        // for shorter distance, add cost of making this element and all elements to its outside equal to the next inner element to the 
        // cost, and make its value equal to element one inner
        if (left_distance > right_distance)
        {
            cost += right_distance * (*right - *(right-1));
            *right = *(right - 1);
        } else 
        {
            // can choose either if equal distance, so choose left
            cost += left_distance * (*(left+1) - *left);
            *left = *(left+1);
        }
    }

    std::cout << cost << "\n";

    return 0;
}