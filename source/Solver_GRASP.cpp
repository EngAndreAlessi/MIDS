#include "Solver_GRASP.hpp"

Solver_GRASP::Solver_GRASP(std::string path) : Solver(path)
{}

void Solver_GRASP::solve(float alpha, int n_iter)
{
    bool *best = greedy_construction(alpha);
    for(int i = 0; i < n_iter; i++)
    {
        bool *sol = greedy_construction(alpha);
        if(sol_length(sol) < sol_length(best))
        {
            best = sol;
        }
        else
        {
            for(int j = 0; j < sol_length(best) - sol_length(sol); j++)
            {
                sol = local_search(sol);
            }
            if(sol_length(sol) < sol_length(best))
            {
                best = sol;
            }
        }
    }
    this->solution->set_solution(best);
}