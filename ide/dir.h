/******************************************************
*
* File name: dir.h
* Author: Andres Casasola Dominguez (andres97dominguez@gmail.com)
* Date: October, 2018
*
*******************************************************/

#ifndef __DIR_H__
#define __DIR_H__

#include <string.h>
//#include "paths.hpp"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "errno.h"
#include <iostream>
#include <vector>

#define SHOW_HIDDEN 1

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
        std::vector<std::string> get_filenames(bool show_hidden);       // 1 Show hidden / 0 Do not
        int new_file(std::string file_name);
        int new_folder(std::string folder_name);
        int new_file(std::string path, std::string file_name);
        int new_folder(std::string path, std::string folder_name);
        bool is_readable(std::string file_name);                        // Readable by owner
        bool is_writeable(std::string file_name);                       // Writeable by owner
        bool is_executable(std::string file_name);                      // Executable by owner
        bool exist(std::string file_name);

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


