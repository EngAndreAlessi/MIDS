#pragma once
#include "Instance.hpp"
#include "Solution.hpp"

class Solver
{
protected:
    Instance *instance;
    int n;
    Solution solution;

public:
    Solver(Instance *instance);
    ~Solver();
    void greedy(float alpha);
    int adj_order(int **adj);
    int max_degree(int *degrees);
    void print_solution();
    void print_degrees(int * degrees);
    int solution_len();
    void local_search(int rmv, int add);
    virtual void solve() = 0;
};
