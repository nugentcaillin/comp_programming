// The ideal time is the sum of time taken for all books,
// but could be longer.

// This time only becomes longer if at least one person finishes a book but cannot start a new one
// this means that they have read every single other book in the collection except for the one the other person is reading
// assuming perfect decision making, each will elect to not read another book such that the other person is forced into this situation,
// so, if the person reading the blocking book could have chosen another book they would have
// this means that this situation only occurs if one book has duration greater than all other books => duration greater than half total,
// and this book always causes a block
// so, time taken is the maximum of the sum of all times and 2 * the duration of longest book

#include <vector>
#include <ranges>
#include <iostream>
#include <algorithm>
#include <numeric>

int main()
{
    int n {};
    std::cin >> n;

    std::vector<int> times {};
    times.reserve(n);

    for ([[maybe_unused]] int _ : std::ranges::views::iota(0, n))
    {
        int curr {};
        std::cin >> curr;
        times.push_back(curr);
    }


    long long max_duration = *std::max_element(times.begin(), times.end());
    long long time_sum = std::accumulate(times.begin(), times.end(), 0ll, [](long long sum, int time) { return sum + time; });
    std::cout << std::max(time_sum, max_duration * 2) << "\n";
    return 0;
}