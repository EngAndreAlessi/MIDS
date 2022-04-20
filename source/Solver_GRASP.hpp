#pragma once
#include "Solver.hpp"
#include <string>

class Solver_GRASP: public Solver
{
public:
    Solver_GRASP(std::string path, std::string log_path);
    void solve(float alpha, int n_iter) override; 
};