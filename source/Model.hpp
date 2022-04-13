#pragma once
#include <CppLib/DataStructures/Vector.h>
#include <CppLib/DataStructures/Set.h>
#include <CppLib/DataStructures/SimpleGraph.h>

using namespace DataStructures;

typedef Set<int, Vector> NodeSet;
//typedef SimpleGraph<int> Graph;

class Graph : public SimpleGraph<int>
{
private:
	using SimpleGraph<int>::neighborsOf;
public:
	Graph() : SimpleGraph<int>(8) {}
	Graph(size_t cap) : SimpleGraph<int>(cap) {}
	
	inline NodeSet neighborsOf(int v){ return NodeSet(SimpleGraph<int>::neighborsOf(v)); }
};
