#include <bits/stdc++.h>


template<class Compare>
class Heap
{
public:
    Heap(int initial_capacity, Compare comp)
    : sum_ {0}
    , container_ {}
    , comp_ {comp}
    {
        container_.reserve(initial_capacity);
    }

    void push(int i)
    {
        container_.push_back(i);
        std::push_heap(container_.begin(), container_.end(), comp_);
        sum_ += i;
    }

    int get_first() const
    {
        if (container_.size() == 0) return 0;
        return container_.at(0);
    }

    int size() const
    {
        return container_.size();
    }
    
    int pop()
    {
        std::pop_heap(container_.begin(), container_.end(), comp_);
        int ret { container_.back() };
        container_.pop_back();
        sum_ -= ret;
        return ret;
    }

    int get_sum() const
    {
        return sum_;
    }

private:
    int sum_;
    std::vector<int> container_;
    Compare comp_;
};


class MinHeap
{
public:
    MinHeap(int initial_capacity)
    : heap_(initial_capacity, std::greater<int> {})
    {}
    MinHeap() : MinHeap(0) {}

    void push(int i) { heap_.push(i); }
    int pop() { return heap_.pop(); }
    int get_sum() const { return heap_.get_sum(); }
    int get_smallest() const { return heap_.get_first(); }
    int size() const { return heap_.size(); }
private:
    Heap<std::greater<int>> heap_;
};


class BalancedDivision
{
public: 
    BalancedDivision(int initial_capacity)
    : first_ { initial_capacity }
    , second_ { initial_capacity }
    {};

    void push(int i) {
        get_smaller_sum_heap().push(i);
        balance();
    }

    int get_difference() const {
        return std::abs(first_.get_sum() - second_.get_sum());
    }


private:

    void balance()
    {
        while (should_move()) move();
    }

    bool should_move()
    {
        int larger_heap_smallest { get_larger_sum_heap().get_smallest() };
        int diff { get_difference() };


        // if moving larger item directly decreases difference, should move 
        if (std::abs(diff - 2 * larger_heap_smallest) < diff) return true;

        // otherwise, if we have the smallest n elements from smallest heap that can offset the move of the larger heap's smallest
        // and reduce difference, should move


        bool offset_found { false };

        std::stack<int> st;
        int sum { 0 };
        MinHeap& smallest = get_smaller_sum_heap();
        while (smallest.size() > 0)
        {
            st.push(smallest.pop());
            sum += st.top();
            int offset_diff { std::abs(diff - 2 * larger_heap_smallest + 2 * sum) };
            if (offset_diff < diff)
            {
                offset_found = true;
                break;
            }
        }

        // repair smaller heap
        while (!st.empty())
        {
            smallest.push(st.top());
            st.pop();
        }

        return offset_found;
    }

    void move()
    {
        std::cout << "diff before move: " << get_difference() << "\n";
        get_smaller_sum_heap().push(get_larger_sum_heap().pop());
        std::cout << "diff after move: " << get_difference() << "\n";
    }

    MinHeap& get_smaller_sum_heap()
    {
        if (first_.get_sum() > second_.get_sum()) return second_;
        return first_;
    }

    const MinHeap& get_smaller_sum_heap() const
    {
        if (first_.get_sum() > second_.get_sum()) return second_;
        return first_;
    }

    MinHeap& get_larger_sum_heap()
    {
        if (first_.get_sum() > second_.get_sum()) return first_;
        return second_;
    }

    const MinHeap& get_larger_sum_heap() const
    {
        if (first_.get_sum() > second_.get_sum()) return first_;
        return second_;
    }

    int get_smaller_sum() const 
    {
        return get_smaller_sum_heap().get_sum();
    }


    MinHeap first_;
    MinHeap second_;
};



int main()
{
    // maintain two heaps, add new number to heap with smaller sum, continually add min of larger heap to smaller heap until smallest number is >= difference in sum
    
    int n {};
    std::cin >> n;

    // since n is small, reserve max space a heap could take to guarantee no realloc
    BalancedDivision division(n);

    for (int i {0}; i < n; ++i)
    {
        int curr {};
        std::cin >> curr;
        division.push(curr);
        std::cout << division.get_difference() << "\n";
    }
    std::cout << division.get_difference() << "\n";
    return 0;
}