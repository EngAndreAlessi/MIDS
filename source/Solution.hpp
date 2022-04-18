#pragma once
#include "Instance.hpp"
#include <string>

class Solution
{
private:
    int n;
    bool *solution;
    Instance inst;
    bool is_in(int vertex);
public:
    Solution(std::string path);
    Solution();
    bool is_valid();
};