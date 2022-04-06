#include "Solver.hpp"
#include <iostream>
#include <vector>

Solver::Solver(Instance instance): instance(instance)
{
    this->n = instance.get_n();
    //std::cout << this->n << std::endl;
    this->solution = new int[this->n];
    for(int i=0; i < this->n; i++)
    {
        solution[i] = 0;
    }
}

/*
Solver::~Solver()
{
    delete this->solution;
    this->solution = NULL;
}
*/

void Solver::greedy(float alpha)
{  
    int *degrees = this->instance.get_degrees();
    int **adj = this->instance.get_adj(); 
    while(adj_order(adj) != 0)
    {    
        print_degrees(degrees);
        float max = 1.0*max_degree(degrees);
        std::cout << "**************************************" << std::endl;
        std::cout << "******** Max degree ******************" << std::endl;
        std::cout << "**************************************" << std::endl;
        std::cout << "Max_degree: " << max << std::endl;
        int i,j;
        std::vector<int> inodes;
        std::cout << "**************************************" << std::endl;
        std::cout << "******** Nodes inserted **************" << std::endl;
        std::cout << "**************************************" << std::endl;
        for(i=0;i<this->n;i++)
        {
            bool geq_alpha_max = (float) degrees[i] >= (alpha * max);
            std::cout << i << ": " << degrees[i] << ">=" << alpha*max << " = " << geq_alpha_max << std::endl;
            if(geq_alpha_max){
                inodes.push_back(i+1);
            }
        }
        int random = rand() % inodes.size();
        int sel_elem = inodes[random];
        std::cout << "**************************************" << std::endl;
        std::cout << "******** Selected element ***********" << std::endl;
        std::cout << "**************************************" << std::endl;
        std::cout << "Selected element: " << sel_elem << std::endl;
        i = sel_elem - 1;
        for(j=0;j<this->n;j++)
        {
            if(adj[i][j] == 1)
            {
                adj[i][j] = 0;
                adj[j][i] = 0;
                degrees[i]--;
                degrees[j]--;
                for(int k = 0; k < this->n; k++)
                {
                    if(adj[j][k] == 1)
                    {
                        adj[j][k] = 0;
                        adj[k][j] = 0;
                        degrees[j]--;
                        degrees[k]--;
                    }
                    
                }
            }
            
        }
        this->solution[i] = 1;
        print_solution();
    }
}

int Solver::adj_order(int **adj)
{
    int i,j;
    int order = 0;
    for(i=0;i<this->n;i++)
    {
        bool is_empty = true;
        for(j=0;j<this->n;j++)
        {
            if(adj[i][j] == 1){
                is_empty = false;
                break;
            }
        }
        if(is_empty == false){
            order++;
        }
    }
    return order;
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

void Solver::print_degrees(int * degrees)
{
    std::cout << "**************************************" << std::endl;
    std::cout << "******** Print Degrees ***************" << std::endl;
    std::cout << "**************************************" << std::endl;
    int i;
    for(i=0;i<this->n;i++)
    {
        std::cout << i+1 << ": " << degrees[i] << "   ";
    }
    std::cout << std::endl;
}

void Solver::print_solution()
{
    std::cout << "**************************************" << std::endl;
    std::cout << "******** Print Solution **************" << std::endl;
    std::cout << "**************************************" << std::endl;
    int i;
    for(i=0;i<this->n;i++)
    {
        std::cout << "Node " << i+1 << ": " << this->solution[i] << std::endl; 
    }
}