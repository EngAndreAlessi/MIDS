#include "Instance.hpp"

Instance::Instance(): FileHandler(), model(nullptr) {}

Instance::Instance(std::string path): FileHandler(path)
{
	try_open();
	
	size_t idx0 = path.find_last_of("/");
	size_t idx1 = path.find_last_of(".");
	this->name = path.substr(idx0+1, idx1-idx0-1);
	
	idx1 = idx0;
	idx0 = path.substr(0, idx0).find_last_of("/");
	this->family = path.substr(idx0+1, idx1-idx0-1);
	
    this->n = find_n();
    this->model = new Graph(this->n);
    
	for(int i = 1; i<= this->n; i++)
	{
        this->model->addVertex(i);
    }
    
    fill_adj();
    
    //log_function(print_adj);
    //log_function(print_degrees); 
    //std::cout << adj_order() << std::endl;
    
    close();
}

Instance::~Instance()
{
	if(this->model != nullptr)
		delete this->model;
}

int Instance::find_n()
{
    try_open();
    skip_lines(5);
    
    int n;
    this->file >> n;
    log_message("N", n);
    
    close();
    return n;
}

void Instance::fill_adj() 
{
    try_open();
    skip_lines(8);
    
    int vi, vj;
	
    while(!this->file.eof())
    {
        this->file >> vi >> vj;
        this->model->addEdge_(vi-1, vj-1);
    }
    close();
}

std::string Instance::get_name() const
{
    return this->name;
}

std::string Instance::get_family() const
{
    return this->family;
}

int Instance::get_n() const
{
    return this->n;
}

Graph* Instance::get_model() const
{
    return this->model;
}

void Instance::print_degrees() const
{
	int v;
    for(size_t i = 0; i < this->n; i++)
    {
    	v = i+1;
        std::cout << "Degree of (" << v << ") = " << this->model->degreeOf_(i) << std::endl;
    }
}


NodeSet Instance::neighbors_of(int v) const
{
	return NodeSet(this->model->neighborsOf(v));
}
