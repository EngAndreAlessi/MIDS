#include "Solution.hpp"

Solution::Solution() : DataStructures::Vector<bool>(0), n(0), inst(nullptr) {}

Solution::Solution(Instance* inst_ptr) : DataStructures::Vector<bool>(1)
{
    this->inst = inst_ptr;
    this->resize(inst->get_n());
    this->deg.resize(inst->get_n());
    this->set_empty();
}

Solution& Solution::operator=(const Solution& sol)
{
	this->n = sol.n;
	this->deg = sol.deg;
	this->inst = sol.inst;
	Vector<bool>::operator=( (Vector<bool>) sol);
	return *this;
}

int Solution::get_n() const
{
	/*int qt = 0;
	for(size_t i=0; i < this->getSize(); i++)
		qt += this->get(i);
    return qt;
    */
    return n;
}

int Solution::degree_of(int vtx) const
{
    return this->deg[vtx-1];
}

bool Solution::is_member(int vtx) const
{
    return this->get(vtx-1);
}

NodeSet Solution::get_members() const
{
	size_t sz = this->getSize();
	NodeSet v = NodeSet(sz);
	
	for(size_t i=0; i < sz; i++)
		if(this->get(i))
			v.add(i+1);
	
    return v;
}

Graph* Solution::get_model() const
{
    return inst->get_model();
}

std::string Solution::get_path() const
{
    return inst->get_path();
}

void Solution::set_full()
{
	this->clear();
	this->fill(true);
	this->n = this->getSize();
	Graph *model = this->inst->get_model();
	
    for(size_t i = 0; i < model->countVertices(); i++)
    	this->deg[i] = model->degreeOf(i+1);
}
void Solution::set_empty()
{
	this->n = 0;
	this->clear();
	this->fill(false);
	this->deg.clear();
	this->deg.fill(-1);
}

void Solution::add_vertex(int vtx)
{
	size_t idx = vtx-1;
	
	if(this->isValidIndex(idx) && !this->get(idx))
	{
		this->n++;
		this->set(true, idx);
		
		NodeSet neigh = this->inst->neighbors_of(vtx);
		NodeSet members = this->get_members();
		this->deg[idx] = (neigh ^ members).getSize(); // intersection
		// recalcular o grau dos que se ligam a ele
	}
}

void Solution::rmv_vertex(int vtx)
{
	size_t idx = vtx-1;
	
	if(this->isValidIndex(idx) && this->get(idx))
	{
		this->n--;
		this->set(false, idx);
		this->deg[idx] = -1;
		// recalcular o grau dos q se ligam a eles
	}
}

// TENTAR OTIMIZAR
bool Solution::is_valid() const
{
	if(this->inst == nullptr)
		return false;
	
    size_t i,j;
    size_t sz = this->getSize();
    Graph g = *inst->get_model();
    
    for(i = 0; i < sz; i++)
    {
        if((*this)[i])
        {
            NodeSet neigh = g.neighborsOf(i+1);
            for(j = 0; j < neigh.getSize(); j++)
            {
                if((*this)[neigh.get(j)-1])
                {
                    return false;
                }
                g.removeVertex(neigh.get(j));
            }
        }
    }

    for(i = 0; i < sz; i++)
    {
        if((*this)[i])
        {
            g.removeVertex(i+1);
        }
    }

    return (g.countVertices() == 0);
}

void Solution::print() const
{
	for(size_t i=0; i < this->getSize(); i++)
	{
		if((*this)[i])
		    std::cout << i+1 << " ";
	}
	std::cout << std::endl;
}
