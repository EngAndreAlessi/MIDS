#include <iostream>
#include "Instance.hpp"
#include "Solver.hpp"

using namespace std;

int main()
{
    Instance inst("MANN-a9.mtx");
    Solver solv(&inst);
    
    //solv.greedy(0.95);
    //cout << solv.solution_len() << endl;
    return 0;
}
