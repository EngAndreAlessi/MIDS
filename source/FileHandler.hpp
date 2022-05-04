#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "Macros.hpp"
#include <cstddef>

class FileHandler
{
protected:
    std::string path;
    std::fstream file;

public:
    FileHandler();
    FileHandler(std::string path);
    ~FileHandler();
    
    void open();
    void close();
    void create();
    void try_open();
    void skip_lines(int qt);
    bool is_open() const;
    std::string get_path() const;
    void set_path(std::string path);
    
    static std::filesystem::directory_iterator scan_dir(std::string path);
};
