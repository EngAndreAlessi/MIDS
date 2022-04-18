#include "Solution.hpp"

Solution::Solution(std::string path)
{
    this->inst = Instance(path);
    this->n = inst.get_n();
    for(int i = 0; i < this->n; i++)
    {
        this->solution[i] = false;
    }
}

bool Solution::is_valid()
{
    Graph aux = this->inst.get_model();
    int i,j;
    for(i = 0; i < this->n; i++)
    {
        if(solution[i])
        {
            NodeSet neigh = aux.neighborsOf(i+1);
            for(j = 0; j < neigh.getSize(); j++)
            {
                if(this->solution[neigh.get(j)])
                {
                    return false;
                }
                aux.removeVertex(neigh.get(j));
            }
        }
    }

    for(i = 0; i < this->n; i++)
    {
        if(solution[i])
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