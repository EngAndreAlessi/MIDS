#include "Solution.hpp"

Solution::Solution(std::string path)
{
    this->inst = Instance(path);
    this->n = inst.get_n();
    this->sol = new bool[this->n];
    for(int i = 0; i < this->n; i++)
    {
        this->sol[i] = false;
    }
}

Solution::Solution() {}

Solution::~Solution()
{
    delete this->sol;
}

bool Solution::is_valid()
{
    Graph aux = this->inst.get_model();
    int i,j;
    for(i = 0; i < this->n; i++)
    {
        if(sol[i])
        {
            NodeSet neigh = aux.neighborsOf(i+1);
            for(j = 0; j < neigh.getSize(); j++)
            {
                if(this->sol[neigh.get(j)-1])
                {
                    return false;
                }
                aux.removeVertex(neigh.get(j));
            }
        }
    }

    for(i = 0; i < this->n; i++)
    {
        if(sol[i])
        {
            aux.removeVertex(i+1);
        }
    }

    if(aux.countVertices() == 0)
    {
        return true;
    }
    return false;
}

void Solution::print_solution() const
{
    for(int i = 0; i < this->n; i++)
    {
        if(this->sol[i])
        {
            std::cout << i + 1 << " ";
        }
    }
    std::cout << std::endl;
}

int Solution::get_n() const
{
    return this->n;
}

bool *Solution::get_solution() const
{
    return this->sol;
}

Graph Solution::get_model() const
{
    return this->inst.get_model();
}

std::string Solution::get_path() const
{
    return this->inst.get_path();
}

void Solution::set_solution(bool *sol)
{
    this->sol = sol;
}