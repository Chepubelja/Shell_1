//
// Created by paniv on 23.05.17.
//
#include <boost/lambda/lambda.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <cstring>
#include <string.h>
static int f_flag = 0;
static int h_flag = 0;
using namespace boost::filesystem;
using namespace std;
string spliter(std::string path){
    vector<std::string> names;
    split(names,path,boost::is_any_of("/"));
    return "/" + names.back();
}
void copy_file_to_file(int argc, char* argv[]){
    vector<std::string> directories;
    int index = 0;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0 ){
            h_flag = 1;
        }
        else if (strcmp(argv[i], "-f") == 0){
            f_flag = 1;
        }
        else if (is_directory(argv[i]) || is_regular_file(argv[i])) {
            directories.push_back((std::string)argv[i]);
            index++;
        }
    }
    if (h_flag) {
        cout << "cp [-h|--help] [-f] <file1> <file2> \n"
             "cp [-h|--help] [-f]  <file1> <file2> <file3>... <dir>" << endl;
        exit(1);
    }
    if (f_flag){
        string aa;
        for (int j = 0; j < index - 1; ++j) {
            std::ifstream  src(directories[j], std::ios::binary);
            aa.append(directories[index - 1]);
            aa.append(spliter(directories.at(j)));
            std::ofstream  dst(aa, std::ios::binary);
            dst << src.rdbuf();
            aa.clear();
        }
    } else
    {
        string check;
        cout << "Do you really want to copy it ? [Y or N] : ";
        cin >> check;
        string aa;
        if (check == "Y" || check == "y"){
            for (int j = 0; j < index - 1; ++j){
                if (exists(directories[j])){
                    std::ifstream  src(directories[j], std::ios::binary);
                    aa.append(directories[index - 1]);
                    aa.append(spliter(directories.at(j)));
                    std::ofstream  dst(aa, std::ios::binary);
                    dst << src.rdbuf();
                    aa.clear();
                }
                else {
                    cout << "There is no such file or directory" << endl;
                }
            }
        }
        else{
            exit(1);
        }
    }
}

int main(int argc, char *argv[]) {
    copy_file_to_file(argc, argv);
    return 0;

}

