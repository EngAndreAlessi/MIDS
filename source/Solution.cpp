#include "Solution.hpp"

Solution::Solution() : DataStructures::Vector<bool>(0), n(0), inst(nullptr)
{
	this->deg_updated = false;
	this->validated = false;
	this->status = false;
}

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
	this->deg_updated = sol.deg_updated;
	this->validated = sol.validated;
	this->status = sol.status;
	Vector<bool>::operator=( (Vector<bool>) sol);
	return *this;
}

int Solution::get_n() const
{
    return n;
}

int Solution::degree_of(int vtx)
{
	if(!this->deg_updated)
	{
		int vi,vj;
		size_t i,j,k;
		
		for(i=0; i< this->n; i++)
		{
			this->deg[i] = 0;
			
			if(!this->get(i))
				continue;
			
			vi = i+1;
			NodeSet neigh = this->inst->neighbors_of(vi);
			
			for(j=0; j < neigh.getSize(); j++)
			{
				vj = neigh.get(j);
				k = vj-1;
				
				if(this->get(k))
					this->deg[k]++;
			}
		}
		this->deg_updated = true;
	}
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
    
	this->deg_updated = true;
	this->validated = true;
	this->status = true;
}
void Solution::set_empty()
{
	this->n = 0;
	this->clear();
	this->fill(false);
	this->deg.clear();
	this->deg.fill(0);
	
	this->deg_updated = true;
	this->validated = true;
	this->status = false;
}

void Solution::add_vertex(int vtx)
{
	size_t idx = vtx-1;
	
	if(this->isValidIndex(idx) && !this->get(idx))
	{
		this->n++;
		this->set(true, idx);
		this->deg_updated = false;
		
		// insertion on an invalid solution can turn it into valid
		if(this->validated && !this->status)
			this->validated = false;
		// if the solution is validated and valid, don't need to revalidate
	}
}

void Solution::rmv_vertex(int vtx)
{
	size_t idx = vtx-1;
	
	if(this->isValidIndex(idx) && this->get(idx))
	{
		this->n--;
		this->set(false, idx);
		this->deg_updated = false;
		
		// removal on a valid solution can turn it into invalid
		if(this->validated && this->status)
			this->validated = false;
		// if the solution is validated and invalid, don't need to revalidate
	}
}

// TENTAR OTIMIZAR
bool Solution::is_valid()
{
	if(this->inst == nullptr)
	{
		this->validated = true;
		this->status = false;
	}
	
	if(!this->validated)
	{
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
						this->status = false;
						this->validated = true;
		                return this->status;
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

		this->status = (g.countVertices() == 0);
		this->validated = true;
	}
	return this->status;
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

/*void Solution::print_status(bool keep_inline) const
{
    printf(" %i|%i|%i %s", 
    	deg_updated, 
    	validated, 
    	status,
    	(keep_inline ? " " : "\n")
    );
}*/
