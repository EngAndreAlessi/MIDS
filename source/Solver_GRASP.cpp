#include "Solver_GRASP.hpp"

Solver_GRASP::Solver_GRASP(std::string path, std::string log_path) : Solver(path, log_path)
{}

void Solver_GRASP::solve(float alpha, int n_iter)
{
    Solution *aux = this->solution;
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
                aux[0].set_solution(sol);
                sol = local_search(aux);
            }
            aux[0].set_solution(sol);
            if((sol_length(sol) < sol_length(best)) && aux[0].is_valid())
            {
                best = sol;
            }
        }
    }
    this->solution[0].set_solution(best);
}