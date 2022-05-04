#include <iostream>
#include <vector>
#include <chrono>
#include "Solvers.hpp"

Solver::Solver() : vers(".") {}

Solver::Solver(Instance *inst, std::string version) : vers(version)
{
	this->inst = inst;
    this->best = Solution(inst);
    srand((unsigned) time(NULL));
}

Solver::~Solver() {}

void Solver::set_log_folder(std::string base_folder)
{
	std::string folder = base_folder + "/" + this->vers + "/" + this->inst->get_family();
	std::string file = this->inst->get_name() + ".txt";
	this->set_path(folder + "/" + file);
}

std::string Solver::get_log_folder() const
{
	return this->path;
}

std::string Solver::get_version_name() const
{
	return this->vers;
}

void Solver::log_batch(int n_iter, std::string base_folder)
{
	this->milis = 0;
	this->set_log_folder(base_folder);
	this->create();
	this->open();
	
	
	while(n_iter-- > 0)
	{
        auto start = std::chrono::high_resolution_clock::now();
		Solution sol = this->solve();
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        this->milis += duration.count();
        
        if(!sol.is_valid())
        {
	        log_message("Solution rejected", "");
        	log_function(sol.print);
        	continue;
        }
        
        log_message("Solution accepted", "");
        log_function(sol.print);
        
        this->file << sol.get_n() << "; ";
        this->file << sol.get_members().strFormat(' ') << "; ";
        this->file << duration.count() << std::endl;
	}
	
	this->close();
}

long Solver::get_batch_duration() const
{
	return this->milis;
}

Solution Solver::get_best_solution() const
{
	return this->best;
}

bool Solver::update_best_solution(Solution &sol)
{
	if(sol.is_valid() && (sol.get_n() < this->best.get_n() || !this->best.is_valid()))
	{
		this->best = sol;
		return true;
	}
	else
		return false;
}

//==================================================
// construction heuristic solver
//==================================================

GreedyMethod::GreedyMethod() : Solver(){}
GreedyMethod::GreedyMethod(Instance *inst, float alpha) : Solver(inst, "greedy-"), alpha(alpha)
{
	std::stringstream ss;
	ss << alpha;
	this->vers += ss.str();
}
Solution GreedyMethod::solve()
{
	log_message("\n>>> Begin of greedy solver...", "");
	
	int v;
    size_t i, j;
    
    // copy of instance graph and new solution
    Graph g = *this->inst->get_model();
    Solution sol = Solution(this->inst);
    
    // inserts zero degree nodes
    for(i = 0; i < g.countVertices(); i++)
    {
        if(g.degreeOf_(i) == 0)
        {
        	v = i+1;
        	sol.add_vertex(v);
        	log_message("Zero degree node added to greedy solution", v);
        }
    }
	log_message("\nNew solution", "");
    
    // remove from graph the added nodes
    NodeSet n = sol.get_members();
    for(i=0; i < n.getSize(); i++)
    {
    	j = g.indexOf(n.get(i));
    	g.removeVertex_(j);
    }
    
	log_message("Starting loop for remaninig nodes (qt)", g.countVertices());
    
    // Preallocated array of vertices
    NodeArray candidates = NodeArray(g.countVertices());
    
    // While there are vertices in the graph
    while(g.countVertices() > 0)
    {
    	// Get max degree
    	int max_deg = g.degreeOf_(0);
	    for(i = 1; i < g.countVertices(); i++)
	    {
	    	int aux = g.degreeOf_(i); 
	    	if(aux > max_deg)
	    	{
	    		max_deg = aux;
	    	}
	    }
	    
        // Select nodes with degree >= max * alpha into inodes
        candidates.clear();
	    for(i = 0; i < g.countVertices(); i++)
	    {
	    	if((float) g.degreeOf_(i) >= max_deg * this->alpha)
	    	{
		    	v = g.getVertex(i);
	    		candidates.pushBack(v);
	    	}
	    }
        // Add random node from candidates to solution
        int random_idx = rand() % candidates.getSize();
        v = candidates[random_idx];
        sol.add_vertex(v);
    	log_message("Random selected node added to greedy solution", v);
    	if(v == 0)
    		exit(1);
        
        // Remove it and its neighbors from copied graph
        i = g.indexOf(v);
        NodeSet neigh = g.neighborsOf_(i);
        g.removeVertex_(i);
    	log_message(" -> Neighbors removed", (std::string) neigh);
        
        for(i = 0; i < neigh.getSize(); i++)
        {
			j = g.indexOf(neigh.get(i));
			g.removeVertex_(j);
        }
    }
    update_best_solution(sol);
    return sol;
}

//==================================================
// local optimization heuristic solver
//==================================================

LocalSearch::LocalSearch() : Solver(){}
LocalSearch::LocalSearch(Instance *inst) : Solver(inst, "localsearch"){}
Solution LocalSearch::solve()
{
    int n = this->inst->get_n();
    Solution sol = this->best;
    NodeArray candidates;
    
    for(size_t i=0; i < n; i++)
    {
    	if(sol.is_member(i+1))
    		candidates.pushBack(i);
	}
	
    int random_idx = rand() % n;
    sol.add_vertex(random_idx + 1);
    
    update_best_solution(sol);
    return (sol.is_valid() ? sol : this->best);
}

//==================================================
// "GRASP" metaheuristic solver
//==================================================

Grasp::Grasp() : Solver(){}
Grasp::Grasp(Instance *inst, Solver* initializer, Solver* localsearch, int max_iter) : Solver(inst, "GRASP[")
{
	this->max_iter = max_iter;
	this->init = initializer;
	this->ls = localsearch;
	this->vers += initializer->get_version_name() + "+" + localsearch->get_version_name() + "]";
}
Solution Grasp::solve()
{
	this->best = this->init->solve();
	Solution curr;
	
	for(int i = 0; i < max_iter; i++)
    {
    	// construct a new solution
        curr = this->init->solve();
        // try to update the best-known
        if(!update_best_solution(curr))
        {
        	// if not, apply a local search method
            for(int j = 0; j < curr.get_n() - this->best.get_n(); j++)
            {
            	this->ls->update_best_solution(curr);
                curr = this->ls->solve();
            }
            update_best_solution(curr);
        }
    }
    
    return curr;
	
	/*
    Solution *aux = this->solution;
    bool *best = greedy_construction(alpha);
    for(int i = 0; i < n_iter; i++)
    {
        bool *sol = greedy_construction(alpha);
        if(sol_length(sol) < sol_length(best))
        {
            best = sol;
        }
        else
        {
            for(int j = 0; j < sol_length(best) - sol_length(sol); j++)
            {
                aux[0].set_solution(sol);
                sol = local_search(aux);
            }
            aux[0].set_solution(sol);
            if((sol_length(sol) < sol_length(best)) && aux[0].is_valid())
            {
                best = sol;
            }
        }
    }
    this->solution[0].set_solution(best);
	*/
	return this->best;
}
