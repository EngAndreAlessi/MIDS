#include <iostream>
#include <cstdlib>
#include "Solver_GRASP.hpp"

using namespace std;

int main()
{
    Solver_GRASP solver("MANN-a9.mtx");
    solver.solve(0.95, 10);
    solver.print_solution();
    return 0;
}
