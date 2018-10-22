
#include "dir.h"

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


std::vector<string> Dir::get_filenames(bool show_hidden){
    if(dir_path != ""){
        dir = opendir(dir_path.c_str());
        if(dir != NULL){
            while((ent = readdir(dir)) != NULL){
                string name(ent->d_name);       // Create string with the name of the file found
                if(show_hiden || name[0] != '.'){   // Solved with Karnaugh
                    filenames.push_back(name);      // Push the string name
                }else{

                }
            }  // If error, errno is set properly
            closedir (dir);
        } // If error, errno is set properly
    }

    return filenames;
}

int Dir::new_file(std::string file_name){
    string full_path = dir_path + "/" + file_name;
     if(creat(full_path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) < 0){
        return -1;
    }   
    return 1;
}

int Dir::new_folder(std::string folder_name){
    string full_path;
    full_path = dir_path + "/" + folder_name;
    if(mkdir(full_path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) < 0)
        return -1;
    else
        return 1;
}

int Dir::new_file(std::string path, std::string file_name){
    string full_path = path + "/" + file_name;
     if(creat(full_path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) < 0){
        return -1;
    }   
    return 1;
}

int Dir::new_folder(std::string path, std::string folder_name){
    string full_path = full_path = path + "/" + folder_name;
    if(mkdir(full_path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) < 0)
        return -1;
    else
        return 1;
}

bool Dir::is_readable(std::string file_name){
    struct stat st;
    string full_path = dir_path + "/" + file_name;
    stat(full_path.c_str(), &st);
    mode_t mode = st.st_mode;
    if(mode & S_IRUSR)
        return 1;
    else
        return 0;
}

bool Dir::is_writeable(std::string file_name){
    struct stat st;
    string full_path = dir_path + "/" + file_name;
    stat(full_path.c_str(), &st);
    mode_t mode = st.st_mode;
    if(mode & S_IWUSR)
        return 1;
    else
        return 0;
}

bool Dir::is_executable(std::string file_name){
    struct stat st;
    string full_path = dir_path + "/" + file_name;
    stat(full_path.c_str(), &st);
    mode_t mode = st.st_mode;
    if(mode & S_IXUSR)
        return 1;
    else
        return 0;
}

bool Dir::exist(std::string file_name){}