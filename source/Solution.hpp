#pragma once
#include "Instance.hpp"
#include <string>

class Solution
{
protected:
    int n;
    bool *sol;
    Instance inst;

    bool is_in(int vertex);
public:
    Solution(std::string path);
    Solution();
    ~Solution();
    bool is_valid();
    void print_solution() const;
    int get_n() const;
    bool *get_solution() const;
    Graph get_model() const;
    void set_solution(bool *sol);
};