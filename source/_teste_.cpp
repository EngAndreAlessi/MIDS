//		clear && g++ _teste_.cpp -o teste Model.cpp && ./teste && rm teste
//		clear && g++ _teste_.cpp -o teste Model.cpp && valgrind ./teste && rm teste

#include "Model.hpp"
using namespace DataStructures;

void testSets();
void testGraphs();

int main()
{	
	testSets();
	testGraphs();
	return 0;
}

void testSets()
{
	std::cout << "\nconjunto 1\n";
	NodeSet s1 = NodeSet(10);
	s1.print();
	
	s1.add(0);
	s1.add(1);
	s1.add(2);
	s1.add(3);
	s1.add(2);
	s1.add(8);
	s1.print();
	
	std::cout << "\nconjunto 2\n";
	NodeSet s2;
	s2 = NodeSet(10);
	s2.print();
	
	for(int i=0; i<10; i++)
		s2.add(i+1);
	s2.print();
	
	std::cout << "\noperações de conjunto\n";
	std::cout << " união (+) : ";
	(s1 + s2).print();
	std::cout << " intersecção (^) : ";
	(s1 ^ s2).print();
	std::cout << " diferença (-) : ";
	(s1 - s2).print();
	
	std::cout << "\nconversões de tipo\n";
	Vector<int> *v = (Vector<int>*) ((Sequence<int>*) &s1);
	v->pushBack(2);
	v->print();
}

void testGraphs()
{
	std::cout << "\ngrafo inicial: semi-completo, não possui arestas(v,v)\n";
	//aloca um grafo para 5 vértices inicialmente
	Graph g1 = Graph(5);
	int vi, vj;
	
	//adiciona vértices
	for(int i=0; i<5; i++)
		g1.addVertex(i*2);
	
	//adiciona arestas "fora de ordem"
	for(int i=0; i < g1.countVertices(); i++)
	{
		vi = g1.getVertex(i);
		
		for(int j= g1.countVertices(); j > i; j--)
		{
			vj = g1.getVertex(j-1);
			
			if(i != j-1)
				g1.addEdge(vi, vj);
		}
	}
	g1.print();
	
	std::cout << "\nremoção do vértice (4)\n";
	//remove o vértice (4)
	g1.removeVertex(g1.getVertex(2));
	g1.print();
	
	//remove a aresta (8, 0)
	std::cout << "\nremoção da aresta (8,0)\n";
	g1.removeEdge(8, 0);
	g1.print();
	
	std::cout << "\ngrafo com mais alterações\n";
	//adiciona vértices e arestas unidirecionais
	//testa a restrição de unicidade de vértice e aresta
	g1.addVertex(1);
	g1.addVertex(8);
	g1.addArrow(1,8);
	g1.addArrow(1,0);
	g1.addArrow(1,8);
	g1.print();
	
	std::cout << "\nvizinhança de (2)\n";
	//obtém a vizinhança de um vértice
	g1.neighborsOf(2).print();
}
