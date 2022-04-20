#pragma once
#include "Solution.hpp"
#include <string>
#include <fstream>

class Solver
{
protected:
    int n;
    Solution *solution;
    std::string path;
    std::ofstream file;
    std::string log_path;

    void open();
    void close();
    inline void try_open();

public:
    Solver(std::string path, std::string log_path);
    Solver();
    ~Solver();
    bool *greedy_construction(float alpha);
    bool *local_search(Solution *solution);
    int *find_degrees(Graph model);
    int max_degree(int *degrees);
    int sol_length(bool *sol);
    void print_solution() const;
    void print_degrees(int *degrees) const;
    int get_n() const;
    bool is_solution_valid();
    void write_log(int n_iter);
    virtual void solve(float alpha, int n_iter) = 0;
};
