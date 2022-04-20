#pragma once
#include <string>
#include <fstream>
#include "Model.hpp"
#include "Macros.hpp"

class Instance
{
protected:
    int n;
    Graph model;
    std::string path;
    std::ifstream file;

    void open();
    void close();
    inline void try_open();
    inline void skip_lines(int qt);
    int find_n();
    void fill_adj();
    
public:
    Instance(std::string path);
    Instance();
    int get_n() const;
    Graph get_model() const;
    std::string get_path() const;
    void print_degrees() const;
}; 