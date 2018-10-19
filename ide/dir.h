/******************************************************
* File name: dir.h
* Author: 
* Date: 
*
*******************************************************/

#ifndef __DIR_H__
#define __DIR_H__

#include <string.h>
//#include "paths.hpp"
#include <dirent.h>
#include <sys/types.h>
#include <iostream>
#include <vector>

class Dir
{
	public:
		
        Dir();
        Dir(std::string path);
	virtual ~Dir();
		
        // Functions
        
        void set_path(std::string path);
        std::string get_path();
        int get_num_files();
        std::vector<std::string> get_filenames();
        
	private:
		
        DIR *dir;                   // Dir handler
        struct dirent *ent;         // Dirent structure
        std::string dir_path;
        //std::string parent_folder;
        int dir_size;
        int num_files;
        int num_folders;
        std::vector<std::string> filenames;


};


#endif //__DIR_H__


