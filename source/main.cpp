#include <iostream>
#include <cstdlib>
#include "Solver_GRASP.hpp"
#include <filesystem>
#include <cstddef>

int main()
{
    std::string path = "bases/DIMACS/";
    for(const auto & entry : std::filesystem::directory_iterator(path))
    {
        std::string name = entry.path().string();
        std::string aux = name.substr(name.find_last_of("/")+1);
        std::string log_name = "logs/" + aux.substr(0, aux.find(".")) + ".txt";
        std::cout << name << std::endl;
        std::cout << log_name << std::endl;
        Solver_GRASP solver(name, log_name);
        solver.write_log(10);
    }

    path = "bases/BHOSLIB/";
    for(const auto & entry : std::filesystem::directory_iterator(path))
    {
        std::string name = entry.path().string();
        std::string aux = name.substr(name.find_last_of("/")+1);
        std::string log_name = "logs/" + aux.substr(0, aux.find(".")) + ".txt";
        std::cout << name << std::endl;
        std::cout << log_name << std::endl;
        Solver_GRASP solver(name, log_name);
        solver.write_log(10);
    }
    
    
    //Solver_GRASP solver("bases/DIMACS/brock200-2.mtx", "logs/brock200-2.txt");
    //solver.write_log(10);
    
    return 0;
}
