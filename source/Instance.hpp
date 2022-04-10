#pragma once
#include <string>
#include <fstream>
#include "Macros.hpp"

class Instance
{
private:
    int n;
    int **adj;
    int *degrees;
    std::string path;
    std::ifstream file;
    
    // interação com arquivo
    void open();
    void close();
    inline void try_open();
    inline void skip_lines(int qt);
    int find_n();
    void fill_adj_and_degrees();
    
public:
    Instance(std::string path);
    ~Instance();
    
    // manipulação de dados
    void remove_node(int node);
    int ** get_adj();
    int get_n();
    int *get_degrees();
	
    // impressão
    void print_degrees();
    void print_adj();
}; 
