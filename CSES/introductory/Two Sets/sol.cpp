#include <bits/stdc++.h>

class MinHeap {
public:
    MinHeap(int max_size)
    : sum_ {0}
    , container_ {}
    {
        container_.reserve(max_size);
    }

    long long getSum() const { return sum_; }

    void push(int n)
    {
        container_.push_back(n);
        std::push_heap(container_.begin(), container_.end(), std::greater<int> {});
        sum_ += n;
    }

    int pop()
    {
        std::pop_heap(container_.begin(), container_.end(), std::greater<int> {});
        int smallest { container_.back() };
        container_.pop_back();
        sum_ -= smallest;
        return smallest;
    }

    long long operator-(const MinHeap& rhs) const
    {
        return getSum() - rhs.getSum();
    }

    void print() const
    {
        std::cout << container_.size() << "\n";
        for (const int n: container_)
        {
            std::cout << n << " ";
        }
        std::cout << "\n";
    }

private:
    long long sum_;
    std::vector<int> container_;
};


int main()
{
    int n {};
    std::cin >> n;

    MinHeap first(n);
    MinHeap second(n);

    // start with all numbers in first set, then repetitively move smallest number from larger set into smaller set until difference is 1 or zero
    for (int i {1}; i <= n; ++i)
    {
        first.push(i);
    }

    // repetitively move smallest element from larger set into smallest set until difference is 1 or zero
    while (std::abs(first - second) > 1)
    {
        if (first - second > 0) second.push(first.pop());
        else first.push(second.pop());
    }

    if (first - second != 0) {
        std::cout << "NO\n";
        return 0;
    }
    std::cout << "YES\n";
    first.print();
    second.print();

    

    return 0;
}