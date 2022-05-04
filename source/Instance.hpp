#pragma once
#include <string>
#include <iostream>
#include "Macros.hpp"
#include "FileHandler.hpp"

#define CPPLIB_ABS_INC_PATH_F
#include "CppLib/DataStructures/header/Vector.h"
#include "CppLib/DataStructures/header/Set.h"

typedef DataStructures::Vector<int> NodeArray;
typedef DataStructures::Vector<bool> EdgeArray;
typedef DataStructures::Set<int, DataStructures::Vector> NodeSet;

class Graph
{
public:
	NodeArray *vertex = nullptr;
	DataStructures::Vector<EdgeArray*> *relation = nullptr;	
public:

	Graph()
	{
		log_message("empy", "");
		vertex = nullptr;
		relation = nullptr;
	}
	
	Graph(size_t init_cap)
	{
		log_message("normal", "");
		if(init_cap==0)
			throw;
		
		vertex = new NodeArray(init_cap);
		relation = new DataStructures::Vector<EdgeArray*>(init_cap);
	}
	
	Graph(const Graph& g)
	{	
		size_t size = g.countVertices();
		vertex = new NodeArray(size);
		relation = new DataStructures::Vector<EdgeArray*>(size);
		NodeArray v;
		
		for(size_t i=0; i < size; i++)
		{
			vertex->pushBack(g.getVertex(i));
			relation->pushBack(new EdgeArray(size));
			
			for(size_t j=0; j < size; j++)
			{
				bool weight = g.getEdge_(i,j);
				(*relation)[i]->pushBack(weight);
			}
		}
	}
	
	virtual ~Graph()
	{
		if(vertex != nullptr)
		{
			delete vertex;
			vertex = nullptr;
		}
		if(relation != nullptr)
		{
			for(size_t i=0; i < relation->getSize(); i++)
				delete (*relation)[i];
			delete relation;
			relation = nullptr;
		}
	}
	
	Graph operator=(const Graph& g)
	{
		this->~Graph();
		
		size_t size = g.countVertices();
		vertex = new NodeArray(size);
		relation = new DataStructures::Vector<EdgeArray*>(size);
		NodeArray v;
		
		for(size_t i=0; i < size; i++)
		{
			vertex->pushBack(g.getVertex(i));
			relation->pushBack(new EdgeArray(size));
			
			for(size_t j=0; j < size; j++)
			{
				bool weight = g.getEdge(i,j);
				(*relation)[i]->pushBack(weight);
			}
		}
		return *this;
	}
	
	inline bool isAllocated() const { return (this->vertex != nullptr && this->relation != nullptr); }
	inline size_t indexOf(int v) const { return vertex->indexOf(v); }
	
	inline bool contains(int v) const { return contains_(indexOf(v)); }
	inline bool contains_(size_t idx) const { return vertex->isValidIndex(idx); }
	
	inline bool contains(int v1, int v2) const { return contains_(indexOf(v1), indexOf(v2)); }
	bool contains_(size_t idx1, size_t idx2) const 
	{
		if(vertex->isValidIndex(idx1) && vertex->isValidIndex(idx2))
			return (*relation)[idx1]->get(idx2);
		else
			return false;
	}
	
	inline size_t getSize() const { return countVertices() + countEdges(); }
	inline size_t countVertices() const { return vertex->getSize(); }
	size_t countEdges() const 
	{
		size_t qt = 0;
		size_t size = vertex->getSize();
		
		for(size_t i=0; i<size; i++)
			qt += degreeOf_(i);
		return qt;
	}
	
	inline int degreeOf(int v) const { return degreeOf_(indexOf(v)); }
	int degreeOf_(size_t idx) const 
	{
		if(!vertex->isValidIndex(idx))
			return -1;
		
		int degree = 0;
		EdgeArray *edges = (*relation)[idx];
		
		for(size_t i=0; i < edges->getSize(); i++)
				degree += edges->get(i);
		
		return degree;
	}
	
	//acesso e manipulação
	inline int getVertex(size_t idx) const { return vertex->get(idx); }
	
	void addVertex(int v)
	{
		if(!vertex->contains(v))
		{
			int qt = countVertices();
			
			for(size_t i=0; i<qt; i++)
				(*relation)[i]->pushBack(false);
			
			vertex->pushBack(v);
			relation->pushBack(new EdgeArray(qt+1));
			(*relation)[qt]->fill(false);
		}
	}
	
	inline void removeVertex(int v) { removeVertex_(indexOf(v)); }
	void removeVertex_(size_t idx)
	{
		if(vertex->isValidIndex(idx))
		{
			delete (*relation)[idx];
			vertex->erase(idx);
			relation->erase(idx);
			
			for(size_t i=0; i < vertex->getSize(); i++)
			{
				(*relation)[i]->erase(idx);
			}
		}
	}
	
	inline bool getEdge(int v1, int v2) const { return getEdge_(indexOf(v1), indexOf(v2)); }
	bool getEdge_(size_t idx1, size_t idx2) const 
	{
		if(vertex->isValidIndex(idx1) && vertex->isValidIndex(idx2))
			return (*relation)[idx1]->get(idx2);
		else
			return false;
	}
	
	inline void addEdge(int v1, int v2) { addEdge_(indexOf(v1), indexOf(v2)); }
	void addEdge_(size_t idx1, size_t idx2)
	{
		if(vertex->isValidIndex(idx1) && vertex->isValidIndex(idx2))
		{
			(*relation)[idx1]->set(true, idx2);
			(*relation)[idx2]->set(true, idx1);
		}
	}
	
	inline void removeEdge(int v1, int v2) { removeEdge_(indexOf(v1), indexOf(v2)); }
	void removeEdge_(size_t idx1, size_t idx2)
	{
		if(vertex->isValidIndex(idx1) && vertex->isValidIndex(idx2))
		{
			(*relation)[idx1]->set(false, idx2);
			(*relation)[idx2]->set(false, idx1);
		}
	}
	
	void clear()
	{
		if(!isAllocated())
			return;
		
		this->vertex->clear();
		for(int i=0; i < relation->getSize(); i++)
			delete (*relation)[i];
		this->relation->clear();
	}
	
	inline NodeArray neighborsOf(int v) const { return neighborsOf_(indexOf(v)); }
	NodeArray neighborsOf_(size_t idx) const 
	{
		NodeArray neigh = NodeArray(1);
		if(this->vertex->isValidIndex(idx))
		{
			EdgeArray *edges = (*relation)[idx];
			for(size_t i=0; i < edges->getSize(); i++)
				if(edges->get(i))
					neigh.pushBack(vertex->get(i));
		}
		return neigh;
	}
	
	std::string strFormat(char c=' ')
	{
		std::stringstream ss;
		size_t size = vertex->getSize();
		
		for(int i=0; i<size; i++)
		{
			int value = (*vertex)[i];
			ss << "(" << value << "): ";
			ss << neighborsOf_(i).strFormat();
			ss << '\n';
		}
		return ss.str();
	}
	
	inline operator std::string(){ return this->strFormat(); }
	inline virtual void print(){ std::cout << (this->strFormat()) << '\n'; }
	inline virtual void print_v(){ std::cout << (this->vertex->strFormat()) << '\n'; }
};

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
