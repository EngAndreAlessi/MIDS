#include "Instance.hpp"
#include <string>
#include <iostream>
#include <fstream>

Instance::Instance(std::string path): path(path)
{
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
    //print_adj();
    //print_degrees(); 
    //std::cout << adj_order() << std::endl;
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

int Instance::find_n()
{
    std::ifstream file;
    file.open("bases/DIMACS/"+this->path);
    if(file.is_open())
    {
        for(int i = 0; i < 5; i++)
        {
            std::string line;
            file >> line;
            //std::cout << line << std::endl;
        }
        int n;
        file >> n;
        //std::cout << n << std::endl;
        return n;
        
    }
    else 
    {
        std::cout << "File could not be open" << std::endl;
        return 0;
    }
}

void Instance::fill_adj_and_degrees() 
{ 
    std::ifstream file;
    file.open("bases/DIMACS/"+this->path);
    if(file.is_open())
    {
        for(int i = 0; i < 8; i++)
        {
            std::string line;
            file >> line;
            //std::cout << line << std::endl;
        }
        while(true)
        {
            if(file.eof()){
                break;
            }
            int i,j;
            file >> i;
            file >> j;
            //std::cout << i << " " << j << std::endl;
            this->adj[i-1][j-1] = 1;
            this->adj[j-1][i-1] = 1;
            this->degrees[i-1]++;
            this->degrees[j-1]++;
            
        }
    }
    else 
    {
        std::cout << "File could not be open" << std::endl;
    }
}

void Instance::print_degrees()
{
    int i;
    for(i=1;i<=this->n;i++)
    {
        std::cout << "Node " << i << ": " << this->degrees[i-1] << std::endl;
    }
}

void Instance::print_adj()
{
    for(int i = 0; i < this->n; i++)
    {
        for(int j = 0; j < this->n; j++)
        {
            std::cout << this->adj[i][j] << " ";
        }
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