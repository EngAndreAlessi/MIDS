#pragma once
#include <string>
#include <sstream>
#include "FileHandler.hpp"
#include "Instance.hpp"
#include "Solution.hpp"

//==================================================
// "Solver" interface
//==================================================

class Solver : public FileHandler
{
protected:
    long milis;
    Instance *inst;
    Solution best;
    std::string vers;
public:
    Solver();
    Solver(Instance *inst, std::string version="empty");
    virtual ~Solver();
    
    void set_log_folder(std::string base_folder);
    std::string get_log_folder() const;
    std::string get_version_name() const;
    void log_batch(int n_iter, std::string base_folder=".");
    long get_batch_duration() const;
    Solution get_best_solution() const;
    bool update_best_solution(const Solution &sol);
    virtual Solution solve() = 0;
};

//==================================================
// construction heuristic solver
//==================================================

class GreedyMethod : public Solver
{
protected:
	float alpha;
public:
    GreedyMethod();
    GreedyMethod(Instance *inst, float alpha);
    Solution solve() override;
};

//==================================================
// local optimization heuristic solver
//==================================================

class LocalSearch : public Solver
{
public:
    LocalSearch();
    LocalSearch(Instance *inst);
    Solution solve() override;
};

//==================================================
// pure metaheuristic solver
//==================================================

class Grasp : public Solver
{
protected:
	Solver* init;
	Solver* ls;
	int max_iter;
public:
    Grasp();
    Grasp(Instance *inst, Solver* initializer, Solver* localsearch, int max_iter=10);
    Solution solve() override;
};
