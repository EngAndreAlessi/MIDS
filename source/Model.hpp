#pragma once
#define CPPLIB_ABS_INC_PATH_F
#include "CppLib/DataStructures/header/Vector.h"
#include "CppLib/DataStructures/header/Set.h"
#include "CppLib/DataStructures/header/SimpleGraph.h"

typedef DataStructures::Set<int, DataStructures::Vector> NodeSet;

class Graph : public DataStructures::SimpleGraph<int>
{
private:
	using DataStructures::SimpleGraph<int>::neighborsOf;
public:
	Graph();
	Graph(size_t cap);
	NodeSet neighborsOf(int v);
};
