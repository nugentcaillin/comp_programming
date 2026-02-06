#include <set>
#include <iostream>
#include <ranges>

// we cannot place a cube on top of a cube that is smaller or on top of one that comes later
// the first cube always has its own tower
// if we find a cube larger than any of our towers are currently, must start a new tower
// if we find a cube smaller, can place it on existing towers or start new tower

// starting a new tower in this situation will always increase tower count by one, 
// but placing it on existing tower may or may not lead to an additional tower, so we can guarantee that we are not worse off by doing this
// -> always put on existing tower if possible

// when there are multiple towers, putting cube on the smallest tower we can is guaranteed to not be worse than a bigger one, as the potential largest cube
// we can take without creating a new tower 

// so, always put cube on smallest tower possible, or store 

int main()
{
    // maintain sorted list of cubes on top of towers using multiset, set cannot be used due to possibility of duplicates
    std::multiset<int> top_cubes {};

    int n {};
    std::cin >> n;

    for ([[maybe_unused]] int _ : std::ranges::views::iota(0, n))
    {
        // find smallest cube that current cube can be placed on top of if present using binary search
        int curr_cube {};
        std::cin >> curr_cube;
        auto to_insert = top_cubes.upper_bound(curr_cube);


        // remove cube to be placed on top of from top cubes if we are not starting a new pile, then add current cupe to top cubes
        if (to_insert != top_cubes.end()) top_cubes.erase(to_insert);
        top_cubes.insert(curr_cube);
    } 

    std::cout << top_cubes.size() << "\n";
}