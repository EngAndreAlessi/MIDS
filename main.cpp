#include <iostream>
#include "Instance.hpp"
#include "Solver.hpp"

using namespace std;

int main()
{
    Instance inst("MANN-a9.mtx");
    Solver solv(inst);
    solv.greedy(1);
    return 0;
}