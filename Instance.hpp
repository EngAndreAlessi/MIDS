#pragma once
#include <string>
class Instance{
private:
    int n;
    int **adj;
    int *degrees;
    std::string path;
public:
    Instance(std::string path);
    //~Instance();
    int find_n();
    void fill_adj_and_degrees();
    void print_degrees();
    void print_adj();
    void remove_node(int node);
    int ** get_adj();
    int get_n();
    int *get_degrees();
}; 