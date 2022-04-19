#include "Solver.hpp"
#include <iostream>
#include <vector>

Solver::Solver(std::string path)
{
    this->solution =  new Solution(path);
    this->n = this->solution[0].get_n();
}

Solver::Solver(){}

Solver::~Solver()
{
    delete this->solution;
}

bool *Solver::greedy_construction(float alpha)
{
    int i, j;
    int *degrees;
    srand( (unsigned)time(NULL) );
    // Get the graph and the solution
    Graph model = this->solution[0].get_model();
    bool *sol = new bool[this->n];
    for(i = 0; i < this->n; i++)
    {
        sol[i] = false;
    }
    // While there are vertices in the graph
    while(model.countVertices() != 0)
    {
        // Get the degrees
        degrees = find_degrees(model);

        // Remove zero degrees
        for(i = 0; i < this->n; i++)
        {
            if(degrees[i] == 0)
            {
                model.removeVertex(i+1);
                sol[i] = true;
            }
        }
        // Insert nodes with degree >= max * alpha into inodes
        float max = 1.0 * max_degree(degrees);
        std::vector<int> inodes;
        for(i = 0; i < this->n; i++)
        {
            bool geq_alpha_max = ((float) degrees[i]) >= (alpha * max);
            if(geq_alpha_max)
            {
                inodes.push_back(i+1);
            }
        }
        // Select random node i from inodes
        int random = rand() % inodes.size();
        int sel_elem = inodes[random];
        i = sel_elem - 1;
        // Remove neighbors of i
        NodeSet neigh = model.neighborsOf(i);
        for(j = 0; j < neigh.getSize(); j++)
        {
            model.removeVertex(neigh.get(j));
        }
        // Remove i from model and insert it into solution
        model.removeVertex(i+1);
        sol[i] = true;
    }
    delete degrees;
    return sol;
}

int *Solver::find_degrees(Graph model)
{
    int *degrees = new int[this->n];
    for(int i = 0; i < this->n; i++)
    {
        if(model.contains(i+1))
        {
            degrees[i] = model.degreeOf(i+1);
        }
        else
        {
            degrees[i] = -1;
        }
    }
    return degrees;
}

int Solver::max_degree(int *degrees)
{
    int max = degrees[0];
    for(int i = 1; i < this->n; i++)
    {
        if(degrees[i] > max){
            max = degrees[i];
        }
    }   
    return max;
}

bool *Solver::local_search(bool *sol)
{
    std::vector<int> inodes;
    for(int i = 0; i < this->n; i++)
    {
        if(sol[i])
        {
            inodes.push_back(i);
        }
    }
    int rand1 = rand() % inodes.size();
    int rand2 = rand() % inodes.size();
    while(rand2 == rand1)
    {
        rand2 = rand() % inodes.size();
    }
    rand1 = rand() % this->n;
    sol[rand1] = true;
    return sol;
}

void Solver::print_solution() const
{
    this->solution->print_solution();
}

int Solver::sol_length(bool *sol)
{
    int sum = 0;
    for(int i = 0; i < this->n; i++)
    {
        if(sol[i])
        {
            sum++;
        }
    }
    return sum;
}