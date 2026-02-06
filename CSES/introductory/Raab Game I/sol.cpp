#include <bits/stdc++.h>

void solve()
{
    int n {};
    int a {};
    int b {};
    std::cin >> n >> a >> b;

    // we can always make scores of zero for both a and b by forcing a draw
    // we can make any number of wins from 1 to n - 1 for either player, but we force the other player to have at least one win
    // so, scores of zero for both, or each player having at least one and a + b < n is possible, all else is not

    // can play at most n games
    if (a + b > n) 
    {
        std::cout << "NO\n";
        return;
    }

    // having a score of 1+ for one player forces a score of at least one for other player, since using high cards against low cards
    // leaves at least one low card that must be used against a high card
    if (!((a > 0 && b > 0) || (a == 0 && b == 0)))
    {
        std::cout << "NO\n";
        return;
    }

    std::cout << "YES\n";

    // if a solution exists, we can have player b pick exclusively 1 to n for each turn
    // player a can force a score of a, b by first picking b + 1 through a + b + 1, winning a games
    // then, picking 1 through b, losing b games. Then, draws can be done for rest of games

    int a_win_start { b + 1 };
    int a_win_end { a + b };
    int a_lose_start { 1 };
    int a_lose_end { b };
    int a_draw_start { a_win_end + 1 };
    int a_draw_end { n };

    // player a moves
    for (int i : std::ranges::views::iota(a_win_start, a_win_end + 1)) std::cout << i << " ";
    for (int i : std::ranges::views::iota(a_lose_start, a_lose_end + 1)) std::cout << i << " ";
    for (int i : std::ranges::views::iota(a_draw_start, a_draw_end + 1)) std::cout << i << " "; 
    std::cout << "\n";

    // player b moves
    for (int i { 1 }; i <= n; ++i) std::cout << i << " ";
    std::cout << "\n";
}

int main()
{
    int t {};
    std::cin >> t;
    for (int i {1}; i <= t; ++i)
    {
        solve();
    }
}