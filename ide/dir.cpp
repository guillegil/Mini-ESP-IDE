
#include "dir.h"
#include "errno.h"

using namespace std;

Dir::Dir(){
    dir = NULL;
    ent = NULL;
    dir_path = "";
    dir_size = 0;
    num_files = 0;
    filenames.clear();
}

Dir::Dir(std::string path){
    dir = NULL;
    ent = NULL;
    dir_path = path;
    dir_size = 0;
    num_files = 0;
    filenames.clear();
}

Dir::~Dir(){
    free(dir);
    free(ent);
}

void Dir::set_path(std::string path){
    dir_path = path;
}

std::string Dir::get_path(){
    return dir_path;
}

int Dir::get_num_files(){
    num_files = -1;

    if(dir_path != ""){
        dir = opendir(dir_path.c_str());
        if(dir != NULL){
            num_files = 0;
            while((ent = readdir(dir)) != NULL){
                num_files++;
            }

            closedir (dir);
        } // If error, errno is set properly

    } // If error, errno is set properly

    return num_files;
}


std::vector<string> Dir::get_filenames(){
    if(dir_path != ""){
        dir = opendir(dir_path.c_str());
        if(dir != NULL){
            while((ent = readdir(dir)) != NULL){
                string name(ent->d_name);       // Create string with the name of the file found
                filenames.push_back(name);      // Push the string name
            }  // If error, errno is set properly
            closedir (dir);
        } // If error, errno is set properly
    }

    return filenames;
}

