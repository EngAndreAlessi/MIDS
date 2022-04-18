#include <iostream>
#include "Instance.hpp"
#include "Solver.hpp"
#include "Model.hpp"

using namespace std;

int main()
{
    //Instance inst("MANN-a9.mtx");
    //inst.print_degrees();
    Graph model;
    model.addVertex(0);
    model.addVertex(1);
    model.addVertex(2);
    model.addEdge(0,1);
    model.addEdge(0,2);
    NodeSet teste = model.neighborsOf(0);
    teste.print();
    return 0;
}
