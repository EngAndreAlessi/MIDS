#include "Instance.hpp"
#include <string>
#include <iostream>
#include <fstream>

Instance::Instance(std::string path): path(path)
{
	open();
    this->n = find_n();
	for(int i = 1; i<= this->n; i++)
    {
        this->model.addVertex(i);
    } 
    
    fill_adj();
    
    //log_function(print_adj);
    log_function(print_degrees); 
    //std::cout << adj_order() << std::endl;
    
    close();
}


void Instance::open()
{
	this->file.open("bases/DIMACS/" + this->path);
    if(!this->file.is_open())
    {
        std::cout << "File could not be open" << std::endl;
        exit(1);
    }
}

void Instance::close() 
{
	if(this->file.is_open())
		this->file.close();
}


inline void Instance::try_open() 
{
	if(!this->file.is_open())
    	open();
}

inline void Instance::skip_lines(int qt) 
{
    try_open();
    std::string line;
    while(qt-- > 0)
    {
    	this->file >> line;
	    log_message("Skipped line", line);
    }
}

int Instance::find_n()
{
    try_open();
    skip_lines(5);
    int n;
    this->file >> n;
    log_message("N", n);
    
    return n;
}

void Instance::fill_adj() 
{
    try_open();
    skip_lines(8);
    
    int i,j;
	
    while(!this->file.eof())
    {
        this->file >> i >> j;
        this->model.addEdge(i,j);
        
    }
}

int Instance::get_n() const
{
    return this->n;
}

Graph Instance::get_model() const
{
    return this->model;
}

void Instance::print_degrees() const
{
    for(int i = 1; i <= this->n; i++)
    {
        std::cout << "Degree of " << i << " = " << this->model.degreeOf(i) << std::endl;
    }
}
