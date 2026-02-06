#include <bits/stdc++.h>


bool comes_before_predecessor(int num, const std::vector<int>& indexes)
{
    // hypothetical number after last number is always placed correctly
    if (num == indexes.size()) return false;
    return indexes.at(num) < indexes.at(num - 1);
}

// returns net change to passes from swap
int perform_swap(int lo, int hi, std::vector<int>& indexes, std::vector<int>& nums)
{
    int net_change { 0 };

    int lo_num { nums.at(lo) };
    int hi_num { nums.at(hi) };
    int lo_succ_num { lo_num + 1 };
    int hi_succ_num { hi_num + 1 };

    bool lo_misplaced_before { comes_before_predecessor(lo_num, indexes) };
    bool lo_successor_misplaced_before { comes_before_predecessor(lo_succ_num, indexes) };
    bool hi_misplaced_before { comes_before_predecessor(hi_num, indexes) };
    bool hi_successor_misplaced_before { comes_before_predecessor(hi_succ_num, indexes) };

    // swap
    indexes.at(nums.at(lo)) = hi;
    indexes.at(nums.at(hi)) = lo;
    std::swap(nums.at(lo), nums.at(hi));

    bool lo_misplaced_after { comes_before_predecessor(lo_num, indexes) };
    bool lo_successor_misplaced_after { comes_before_predecessor(lo_succ_num, indexes) };
    bool hi_misplaced_after { comes_before_predecessor(hi_num, indexes) };
    bool hi_successor_misplaced_after { comes_before_predecessor(hi_succ_num, indexes) };

    // either lo or hi could have successor equal to other as lo and hi refers to indexes, not numbers themselves
    // so either lo_succ or hi_succ could be a duplicate, but not both
    int lo_successor_diff_amount { (lo_succ_num == hi_num) ? 0 : 1};
    int hi_successor_diff_amount { (hi_succ_num == lo_num) ? 0 : 1 };

    // calculate net change from swap moving all possible numbers it could in or out of relative place
    if (lo_misplaced_before && !lo_misplaced_after) --net_change;
    if (!lo_misplaced_before && lo_misplaced_after) ++net_change;
    if (lo_successor_misplaced_before && !lo_successor_misplaced_after) net_change -= lo_successor_diff_amount;
    if (!lo_successor_misplaced_before && lo_successor_misplaced_after) net_change += lo_successor_diff_amount;
    if (hi_misplaced_before && !hi_misplaced_after) --net_change;
    if (!hi_misplaced_before && hi_misplaced_after) ++net_change;
    if (hi_successor_misplaced_before && !hi_successor_misplaced_after) net_change -= hi_successor_diff_amount;
    if (!hi_successor_misplaced_before && hi_successor_misplaced_after) net_change += hi_successor_diff_amount; 

    return net_change;
}


int main()
{
    // number of passes initially is 1 + number of elements such that their immediate predecessor has not been found
    // if we make a swap such that a number that was after its predecessor now comes before, we increase passes by one
    // if we make a swap such that a number that came before its predecessor now comes after, we decrease by one
    // need to check both moved number and its successor for these conditions



    int n{};
    int m{};

    std::cin >> n >> m;

    // store num indexes, use to find predecessor, use n + 1 as starting val -> any number whose predecessor has not been encountered has a predecessor
    // with index greater than itself
    // doing it this way for first pass allows us to reuse the comes_before_predecessor function
    std::vector<int> indexes(n + 1, n + 1);
    std::vector<int> nums;
    nums.reserve(n + 1);
    nums.push_back(-1); // garbage value for one indexing 

    int passes { 0 }; // 0 since 1 comes after its predecessor according to our definitions so far
   for (int i : std::ranges::views::iota(1, n + 1)) // need to leave space for zero for countind to work correctly
   {
        int curr {};
        std::cin >> curr;
        indexes.at(curr) = i;
        if (comes_before_predecessor(curr, indexes)) ++passes;
        nums.push_back(curr);
   }


   // compute passes after each swap
   for (int _ : std::ranges::views::iota(0, m))
   {
        int lo {};
        int hi {};
        std::cin >> lo >> hi;
        passes += perform_swap(lo, hi, indexes, nums);
        std::cout << passes << "\n";
   }
   return 0;
}