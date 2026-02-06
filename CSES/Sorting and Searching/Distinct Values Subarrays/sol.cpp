#include <iostream>
#include <set>
#include <queue>
#include <ranges>

// the number of subarrays where each element is distinct in the entire array is equivalent to the number of subarrays starting at each index. 

// the number of subarrays starting at each index is equivalent to the length of the longest subarray starting at that index such that every element is distinct

// can maintain a set and a queue containing only elements currently in longest subsequence starting at each index to save space, the first element in the 
// queue is the starting index, add elements to set and queue until new element already in set, then queue length is longest subsequence starting at this 'index'.

int main()
{
    int n {};
    std::cin >> n;

    std::queue<int> current_subsequence {};
    std::set<int> seen_numbers {};

    // max is ~n^2, will not fit in int
    long subarray_count {};

    for ([[maybe_unused]] int _ : std::ranges::views::iota(0, n))
    {
        int curr_number {};
        std::cin >> curr_number;

        // as long as curr number will introduce a duplicate, queue contains longest subsequence starting at index of front element
        while (seen_numbers.contains(curr_number))
        {
            subarray_count += current_subsequence.size();
            seen_numbers.erase(current_subsequence.front());
            current_subsequence.pop();
        }

        current_subsequence.push(curr_number);
        seen_numbers.insert(curr_number);
    }

    // for remaining indexes after consuming all numbers, number of subarrays is equivalent to the sum of natural numbers from 1 to length of queue
    long remaining_elements { (int)current_subsequence.size() };
    subarray_count += remaining_elements * ( remaining_elements + 1 ) / 2; // sum of n natural numbers

    std::cout << subarray_count << "\n";
    return 0;
}