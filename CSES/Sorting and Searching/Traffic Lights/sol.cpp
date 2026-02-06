#include <set>
#include <ranges>
#include <iostream>
#include <iterator>


// the longest stretch before adding any lights is x

// each traffic light will take one stretch, and cut it into two portions

// so, maintain sorted list of lights inserted so far, use this to find lights before and after insertion,
// and calculate length that will be cut, 
// also remain sorted list of lengths, update this on every light and longest will be last element

int main()
{
    // 200k cout calls in 1s is tight enough constraints that this is needed
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int x {};
    int n {};
    std::cin >> x >> n;

    std::multiset<int> stretches;
    std::set<int> lights;

    // add bounds to calculate stretch lengths, lights at position 0 or x make no change to longest stretch
    lights.insert(0);
    lights.insert(x);
    stretches.insert(x);

    for ([[maybe_unused]] int _ : std::ranges::views::iota(0, n))
    {
        // insert new light
        int curr_light;
        std::cin >> curr_light;
        auto [new_light, inserted] = lights.insert(curr_light);
        
        // lights at position 0 or x do not change longest stretch and will cause bounds errors
        if (curr_light == 0 || curr_light == x)
        {
            std::cout << *(--stretches.end()) << "\n";
            continue;
        }

        // find length of stretch that this light divides
        auto prev_light = std::prev(new_light, 1);
        auto next_light = std::next(new_light, 1);
        int divided_stretch_len { *next_light - *prev_light };

        // remove divided stretch and add new stretches created
        int left_stretch { *new_light - *prev_light };
        int right_stretch { *next_light - *new_light };
        stretches.erase(stretches.find(divided_stretch_len));
        stretches.insert(left_stretch);
        stretches.insert(right_stretch);

        std::cout << *(--stretches.end()) << "\n";
    }


    return 0;
}