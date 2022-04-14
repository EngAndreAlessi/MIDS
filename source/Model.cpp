#include "Model.hpp"

using namespace DataStructures;

Graph::Graph() : Graph::SimpleGraph<int>(8) {}

Graph::Graph(size_t cap) : Graph::SimpleGraph<int>(cap) {}

NodeSet Graph::neighborsOf(int v)
{
	return NodeSet(SimpleGraph<int>::neighborsOf(v));
}
