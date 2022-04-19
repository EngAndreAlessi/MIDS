#include <iostream>
#include <cstdlib>
#include "Solver_GRASP.hpp"

using namespace std;

int main()
{
    /*
    Solver_GRASP solver("teste.mtx");
    //solver.solve(0.8, 10);
    //solver.print_solution();
    bool * sol = solver.greedy_construction(0.8);
    for(int i = 0; i < solver.get_n(); i++)
    {
        if(sol[i])
        {
            cout << i << " ";
        }
    }
    cout << endl;
    */
    Instance inst("teste.mtx");
    Graph model = inst.get_model();
    model.removeVertex(1);
    cout << model.contains(1) << endl;
    return 0;
}
