// maintain sorted list of children with set, advance and remove with iterator
// need random access, use policy based structure for indexed set from cses handbook
#include <ext/pb_ds/assoc_container.hpp>
#include <iostream>
#include <ranges>
using namespace __gnu_pbds;


// inherit from policy structure to define insertion with iterators like std::set
typedef tree<int, null_type, std::less<int>, rb_tree_tag, tree_order_statistics_node_update> container;
class IndexedSet : public container {
public: 
    template<typename Iter>
    void insert(Iter begin, Iter end)
    {
        while (begin < end)
        {
            container::insert(*begin);
            ++begin;
        }
    }
};




int main()
{
    int n {}; int k {};
    std::cin >> n >> k;

    // fill sorted list of children
    IndexedSet children {};
    auto indices = std::ranges::views::iota(1, n + 1);
    children.insert(indices.begin(), indices.end());

    // skip then remove children until none left
    unsigned int index = 0;
    while (!children.empty())
    {
        index += k;
        index %= children.size();
        auto child_to_remove = children.find_by_order(index);
        std::cout << *child_to_remove << "\n";
        children.erase(child_to_remove);
    }


    return 0;
}