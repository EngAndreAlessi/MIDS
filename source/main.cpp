#include <iostream>
#include <cstdlib>
#include <cstddef>
//#include "Solver_GRASP.hpp"
#include "Solvers.hpp"

using namespace std;

int main(int argc, char** argv)
{
    string bases[] = {
    	"bases/DIMACS/",
    	"bases/BHOSLIB/"
    };
    
    for(string folder : bases)
    {
		for(const auto& entry : FileHandler::scan_dir(folder))
		{
		    string path = entry.path().string();
		    if(argc == 2 && path != argv[1])
				continue;
		    	
		    Instance inst = Instance(path);
		    std::cout << inst.get_family() << "/" << inst.get_name() << std::endl;
		    
		    GreedyMethod s0 = GreedyMethod(&inst, 0.8);
		    s0.log_batch(10, "logs");
		    
		    /*LocalSearch s1 = LocalSearch(&inst);
		    s1.update_best_solution(s0.get_best_solution());
		    s1.log_batch(10, "logs");
		    
		    Grasp s2 = Grasp(&inst, &s0, &s1, 10);
		    s2.log_batch(10, "logs");*/
		}
	}
    
    return 0;
}
