#pragma once
#include <string>
#include <iostream>
#include "Macros.hpp"
#include "FileHandler.hpp"

#define CPPLIB_ABS_INC_PATH_F
#include "CppLib/DataStructures/header/Vector.h"
#include "CppLib/DataStructures/header/Set.h"
#include "CppLib/DataStructures/header/SimpleGraph.h"

typedef DataStructures::Vector<int> NodeArray;
typedef DataStructures::SimpleGraph<int> Graph;
typedef DataStructures::Set<int, DataStructures::Vector> NodeSet;

class Instance : public FileHandler
{
protected:
    int n;
    std::string name;
    std::string family;
    Graph *model;
    
    int find_n();
    void fill_adj();
public:
    Instance();
    Instance(std::string path);
    ~Instance();
    
    std::string get_name() const;
    std::string get_family() const;
    int get_n() const;
    Graph* get_model() const;
    void print_degrees() const;
	NodeSet neighbors_of(int v) const;
};
