#include "Solver.hpp"
#include <iostream>
#include <vector>
#include <chrono>

Solver::Solver(std::string path, std::string log_path)
{
    this->log_path = log_path;
    this->solution =  new Solution(path);
    this->n = this->solution[0].get_n();
    this->path = this->solution[0].get_path();
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
        //std::cout << "Model:" << std::endl;
        //model.print();
        //std::cout << std::endl;
        //print_degrees(degrees);

        // Remove zero degrees
        for(i = 0; i < this->n; i++)
        {
            if(degrees[i] == 0)
            {
                model.removeVertex(i+1);
                //std::cout << "Zero degree removed: " << i+1 << std::endl;
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
        //std::cout << "Selected node: " << i+1 << std::endl;
        // Remove neighbors of i
        NodeSet neigh = model.neighborsOf(i+1);
        for(j = 0; j < neigh.getSize(); j++)
        {
            model.removeVertex(neigh.get(j));
            //std::cout << "Node removed: " << neigh.get(j) << std::endl;
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

bool *Solver::local_search(Solution *solution)
{
    bool *sol = solution[0].get_solution();
    bool *original = sol;
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
    solution[0].set_solution(sol);
    if(solution[0].is_valid())
    {
        return sol;
    }
    else
    {
        return original;
    }
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

int Solver::get_n() const
{
    return this->n;
}

bool Solver::is_solution_valid()
{
    return this->solution[0].is_valid();
}

void Solver::open()
{
	this->file.open(this->log_path);
    if(!this->file.is_open())
    {
        std::cout << "File could not be open" << std::endl;
        exit(1);
    }
}

void Solver::close() 
{
	if(this->file.is_open())
		this->file.close();
}


inline void Solver::try_open() 
{
	if(!this->file.is_open())
    	open();
}

void Solver::write_log(int n_iter)
{
    try_open();
    for(int j = 0; j < n_iter; j++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        solve(0.8, 20);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        bool *sol = this->solution[0].get_solution();
        for(int i = 0; i < this->n; i++)
        {
            if(sol[i])
            {
                file << i + 1 << " ";
            }
        }
        file << ";";
        file << sol_length(sol);
        file << ";";
        file << duration.count();
        file << std::endl;
    }
    close();
}

void Solver::print_degrees(int *degrees) const
{
    for(int i = 0; i < this->n; i++)
    {
        std::cout << i+1 << ": " << degrees[i] << std::endl;
    }
}