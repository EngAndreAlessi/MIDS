#pragma once
#include "Solution.hpp"
#include <string>

class Solver
{
protected:
    int n;
    Solution *solution;

public:
    Solver(std::string path);
    Solver();
    ~Solver();
    bool *greedy_construction(float alpha);
    bool *local_search(bool *sol);
    int *find_degrees(Graph model);
    int max_degree(int *degrees);
    int sol_length(bool *sol);
    void print_solution() const;
    virtual void solve(float alpha, int n_iter) = 0;
};
