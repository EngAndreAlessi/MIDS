#include "FileHandler.hpp"

FileHandler::FileHandler() {}

FileHandler::FileHandler(std::string path): path(path)
{
	open();
}

FileHandler::~FileHandler() 
{
	close();
}


void FileHandler::open()
{    
    log_message("Opening file", this->path);
    this->file.open(this->path);
    
    if(!this->file.is_open())
    {
        std::cout << "File could not be open" << std::endl;
        exit(1);
    }
}

void FileHandler::close() 
{   
	if(this->file.is_open())
	{
	    log_message("Closing file", this->path);
		this->file.close();
	}
}

void FileHandler::create() 
{
	size_t idx = this->path.find_last_of("/");
	
	if(idx < this->path.size())
	{
		std::string folder = this->path.substr(0, idx);
		if(!std::filesystem::exists(folder))
		{
			log_message("Creating non-existing folder", folder);
		    std::filesystem::create_directories(folder);
		}
	}
    
    log_message("Creating file", this->path);
    std::ofstream(this->path);
}


void FileHandler::try_open() 
{
	if(!this->file.is_open())
    	open();
}

void FileHandler::skip_lines(int qt) 
{
    this->try_open();
    std::string line;
    
    while(qt-- > 0)
    {
    	this->file >> line;
	    log_message("Skipped line", line);
    }
}

bool FileHandler::is_open() const
{
	return this->file.is_open();
}

std::string FileHandler::get_path() const
{
    return this->path;
}

void FileHandler::set_path(std::string path)
{
	if(this->file.is_open())
    {
        std::cout << "File already open" << std::endl;
        exit(1);
    }
    this->path = path;
}

std::filesystem::directory_iterator FileHandler::scan_dir(std::string path)
{
	return std::filesystem::directory_iterator(path);
}
