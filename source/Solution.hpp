#pragma once
#define CPPLIB_ABS_INC_PATH_F
#include <string>
#include "Instance.hpp"
#include "CppLib/DataStructures/header/Vector.h"

class Solution : protected DataStructures::Vector<bool>
{
protected:
    Instance *inst;
    DataStructures::Vector<int> deg;
    size_t n;
public:
    Solution();
    Solution(Instance* inst_ptr);
	Solution& operator=(const Solution& sol);
    
    int get_n() const;
    int degree_of(int vtx) const;
    bool is_member(int vtx) const;
    NodeSet get_members() const;
    Graph* get_model() const;
    std::string get_path() const;
    
    void set_full();
    void set_empty();
    void add_vertex(int vtx);
    void rmv_vertex(int vtx);
    bool is_valid() const;
    void print() const;
};
