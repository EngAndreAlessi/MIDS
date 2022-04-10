#include "Instance.hpp"
#include <string>
#include <iostream>
#include <fstream>

Instance::Instance(std::string path): path(path)
{
	open();

    this->n = find_n();
    this->degrees = new int[n];
    this->adj = new int*[this->n];
    for(int i = 0; i < this->n; i++)
    {
        this->adj[i] = new int[n]; 
    }
    for(int i = 0; i < this->n; i++)
    {
        this->degrees[i] = 0;
        for(int j = 0; j < this->n; j++)
        {
            this->adj[i][j] = 0;
        }
    }
    fill_adj_and_degrees();
    
    log_function(print_adj);
    log_function(print_degrees); 
    //std::cout << adj_order() << std::endl;
    
    close();
}

/*
Instance::~Instance()
{
    delete this->degrees;
    this->degrees = NULL;
    delete this->adj;
    for(int i=0;i<this->n;i++)
    {
        this->adj[i] = NULL;
    }
}
*/

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

void Instance::fill_adj_and_degrees() 
{
    try_open();
    skip_lines(8);
    
    int i,j;
	
    while(!this->file.eof())
    {
        this->file >> i >> j;
        i--;
        j--;
	    log_message("N", n);
        //std::cout << i << " " << j << std::endl;
        this->adj[i][j] = 1;
        this->adj[j][i] = 1;
        this->degrees[i]++;
        this->degrees[j]++;
        
    }
}

void Instance::print_degrees()
{
    for(int i=0; i < this->n; i++)
        std::cout << "Node " << (i+1) << ": " << this->degrees[i] << std::endl;
}

void Instance::print_adj()
{
    for(int i = 0; i < this->n; i++)
    {
        for(int j = 0; j < this->n; j++)
            std::cout << this->adj[i][j] << " ";
        
        std::cout << std::endl;
    }
}

void Instance::remove_node(int node)
{
    int i = node - 1;
    int j;
    for(j=0;j<this->n;j++)
    {
        if(this->adj[i][j] == 1){
            this->adj[i][j] = 0;
            this->adj[j][i] = 0;
            this->degrees[i]--;
            this->degrees[j]--;
        }
    }
}

int **Instance::get_adj()
{
    return this->adj;
}

int Instance::get_n()
{
    return this->n;
}

int *Instance::get_degrees()
{
    return this->degrees;
}
