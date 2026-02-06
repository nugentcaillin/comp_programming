#include <bits/stdc++.h>

const int GRID_SIZE { 7 };


typedef std::array<std::array<int, GRID_SIZE>, GRID_SIZE> visited_t;
typedef std::pair<int, int> direction_t;


class CullStrategy {
public:
    CullStrategy(int grid_size)
    : grid_size_ {grid_size}
    {}

    virtual bool should_cull(int x, int y, int dx, int dy, int depth, const visited_t& visited) const = 0;
protected:
    int grid_size_;
};

class CompositeCullStrategy : public CullStrategy {
public:
    CompositeCullStrategy(int grid_size)
    : CullStrategy(grid_size)
    , strategies_ {}
    {}

    void add(std::shared_ptr<CullStrategy> strategy) {
        strategies_.push_back(strategy);
    }

    // false if all strategies suggest not culling, true otherwise
    bool should_cull(int x, int y, int dx, int dy, int depth, const visited_t& visited) const override
    {
        for (std::shared_ptr<CullStrategy> strategy: strategies_)
        {
            if (strategy->should_cull(x, y, dx, dy, depth, visited)) return true;
        }
        return false;
    }
private:
    std::vector<std::shared_ptr<CullStrategy>> strategies_;
};

class BoundsCheckStrategy: public CullStrategy {
public:
    BoundsCheckStrategy(int grid_size)
    : CullStrategy(grid_size)
    {}

    bool should_cull(int x, int y, int dx, int dy, int depth, const visited_t& visited) const override 
    {
        return x + dx < 0 || x + dx >= grid_size_ || y + dy < 0 || y + dy >= grid_size_;
    }
};


// any space that is neither visited nor out of bounds is available
class IsAvailableSpaceStrategy: public CompositeCullStrategy {
public:
    IsAvailableSpaceStrategy(int grid_size)
    : CompositeCullStrategy(grid_size)
    {
        add(std::make_shared<BoundsCheckStrategy>(grid_size));
    }
    
    bool should_cull(int x, int y, int dx, int dy, int depth, const visited_t& visited) const override 
    {
        if (CompositeCullStrategy::should_cull(x, y, dx, dy, depth, visited)) return true;
        return visited[x + dx][y + dy];
    }
};

class EarlyFinishStrategy: public CullStrategy {
public:
    EarlyFinishStrategy(int grid_size, int finish_x, int finish_y, int max_depth)
    : CullStrategy(grid_size)
    , finish_x_ { finish_x }
    , finish_y_ { finish_y }
    , max_depth_ { max_depth }  
    {}

    bool should_cull(int x, int y, int dx, int dy, int depth, const visited_t& visited) const override 
    {
        return x + dx == finish_x_ && y + dy == finish_y_ && depth != max_depth_;
    }
private:
    int finish_x_;
    int finish_y_;
    int max_depth_;
};

// if a move one cell after a move is not visitable, and both cells perpendicular are free,
// that move cuts the grid into two sections
class MoveCutsOffGridStrategy: public CompositeCullStrategy {
public:
    MoveCutsOffGridStrategy(int grid_size)
    : CompositeCullStrategy(grid_size)
    {
        add(std::make_shared<IsAvailableSpaceStrategy>(grid_size));
    }

    bool should_cull(int x, int y, int dx, int dy, int depth, const visited_t& visited) const override 
    {
        // one of dx or dy is alwayx zero due to orthoganal moves so can multiply both to get next move in same direction
        int next_move_dx { dx * 2 };
        int next_move_dy { dy * 2 };

        // don't care about sign since we are considering both perpendicular moves, perpendicular moves obtained by moving 
        // in other axis to current move
        int cross_dx { std::abs(dx) > 0 ? 0 : 1 };
        int cross_dy { std::abs(dy) > 0 ? 0 : 1 };

        // if moving one extra puts us in unavaliable space, and both perpendicular moves are available, cull
        if (
            CompositeCullStrategy::should_cull(x, y, next_move_dx, next_move_dy, depth + 1, visited)
            && !CompositeCullStrategy::should_cull(x, y, dx + cross_dx, dy + cross_dy, depth + 1, visited)
            && !CompositeCullStrategy::should_cull(x, y, dx - cross_dx, dy - cross_dy, depth + 1, visited)
        ) return true;
        return false;

    }

};



class BacktrackingSearch {
public:
    BacktrackingSearch(int grid_size, std::string path)
    : cull_strategy_ { grid_size }
    , visited_ {}
    , path_ { path }
    , count_ { 0 }
    , depth_ { 0 }
    , finish_x_ { 0 }
    , finish_y_ { grid_size - 1 }
    , max_depth_ { grid_size * grid_size }
    {
        cull_strategy_.add(std::make_shared<IsAvailableSpaceStrategy>(grid_size));
        cull_strategy_.add(std::make_shared<EarlyFinishStrategy>(grid_size, finish_x_, finish_y_, max_depth_));
        cull_strategy_.add(std::make_shared<MoveCutsOffGridStrategy>(grid_size));
        dfs(0, 0);
    }

    int get_solution_count() const 
    {
        return count_;
    }

private:
    CompositeCullStrategy cull_strategy_;
    visited_t visited_;
    std::string path_;
    int count_;
    int depth_;
    int max_depth_;
    int finish_x_;
    int finish_y_;
    static const std::array<direction_t, 4> CARDINAL_DIRECTIONS_;

    void before_visit(int x, int y)
    {
        ++depth_;
        visited_.at(x).at(y) = true;
    }
    void after_visit(int x, int y)
    {
        --depth_;
        visited_.at(x).at(y) = false;
    }
    bool is_finish_cell(int x, int y)
    {
        return x == finish_x_ && y == finish_y_;
    }

direction_t direction_from_char(char c)
    {
        switch (c)
        {
        case 'D':
            return { 0 , 1 };
        case 'U':
            return { 0 , -1 };
        case 'R':
            return { 1 , 0 };
        default:
            return { -1 , 0 };
        }
    }   
    
    void dfs(int x, int y)
    {

        before_visit(x, y);
        if (depth_ == max_depth_)
        {
            if (is_finish_cell(x, y))
            {
                ++count_;
                // std::cout << count_ << "\n";
            }
        } else if (path_.at(depth_ - 1) != '?') 
        {
            auto [dx, dy] = direction_from_char(path_.at(depth_ - 1));
            if (!cull_strategy_.should_cull(x, y, dx, dy, depth_ + 1, visited_)) dfs(x + dx, y + dy);
        }
        else {
            for (auto [dx, dy]: CARDINAL_DIRECTIONS_)
            {
                if (!cull_strategy_.should_cull(x, y, dx, dy, depth_ + 1, visited_)) dfs(x + dx, y + dy);
            }
        }
        after_visit(x, y);
    }
};

typedef std::pair<int, int> direction_t;

const std::array<direction_t, 4> CARDINAL_DIRECTIONS 
{{
    { 0, 1 }
    , { 0, -1 }
    , { 1, 0 }
    , { -1, 0 }
    }
};


bool is_valid_move(int x, int y, int dx, int dy)
{
    return x + dx >= 0 && x + dx < GRID_SIZE && y + dy >= 0 && y + dy < GRID_SIZE;
}


int paths (int x, int y, int depth, std::vector<std::vector<std::vector<long long>>>& memo)
{
    // std::cout << x << ", " << y << ", " << depth << "\n";
    if (memo.at(x).at(y).at(depth) >= 0) return memo.at(x).at(y).at(depth);
    if (depth == 0)
    {
        if (x == 0 && y == 0) 
        {
            std::cout << "ret 1\n";
            memo.at(x).at(y).at(depth) = 1;
            return 1;
        }
        memo.at(x).at(y).at(depth) = 0;
        return 0;
    }

    int sum { 0 };
    for (auto [dx, dy]: CARDINAL_DIRECTIONS)
    {
        if (is_valid_move(x, y, dx, dy)) sum += paths(x+dx, y+dy, depth - 1, memo);
    }
    memo.at(x).at(y).at(depth) = sum;
    return sum;
}


int main()
{
    std::string path {};
    
    std::cin >> path;

    BacktrackingSearch search { GRID_SIZE , path};

    std::cout << search.get_solution_count() << "\n"; 

    return 0;
    // to get to the bottom left traversing every cell, we must make 48 moves.
    // the number of down moves needs to be 6 more than up moves
    // number of left and right is equal
    // and sum of up, down, left and right is equal
    // also, down, left and right must all be >= 6

    std::vector<std::vector<std::vector<long long>>> memo(GRID_SIZE, std::vector<std::vector<long long>>(GRID_SIZE, std::vector<long long>(GRID_SIZE * GRID_SIZE, -1)));


    std::cout << paths(0, 6, 48, memo);
    for (int i {0}; i < 49; ++i)
    {
        std::cout << "MOVES: " << i << "\n";
        for (int x {0}; x < 7; ++x)
        {
            for (int y {0}; y < 7; ++y)
            {
                std::cout << memo.at(y).at(x).at(i) << " ";       
            }
            std::cout << "\n";
        }
    }
}