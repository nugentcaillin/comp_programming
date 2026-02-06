#include <set>
#include <iostream>
#include <ranges>

int main()
{
    // maintain sorted list of children, remove one at a time
    std::set<int> children;
    int n {};
    std::cin >> n;
    auto indices = std::ranges::views::iota(1, n + 1);
    children.insert(indices.begin(), indices.end());

    // skip child, and then remove until empty, wrapping round end
    auto curr = children.begin();
    while (!children.empty())
    {
        std::advance(curr, 1);
        if (curr == children.end()) curr = children.begin();
        std::cout << *curr << " ";
        curr = children.erase(curr);
        if (curr == children.end()) curr = children.begin(); // removing could also cause going off end
    }

    std::cout << "\n";

    return 0;
}