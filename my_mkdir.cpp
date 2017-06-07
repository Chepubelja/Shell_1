//
// Created by paniv on 23.05.17.
//

#include <unistd.h>
#include <iostream>
#include <sys/stat.h>
#include <cstring>

using namespace std;
void make_directory(char* directory){
    char cwd[1024];
    char *ptr;
    char *a = (char *) "/";
    ptr = getcwd(cwd, sizeof(cwd));
    struct stat st = {0};
    ptr = strcat(ptr, a);
    ptr = strcat(ptr,directory);
    if (stat(ptr, &st) == -1) {
        mkdir(ptr, 0700);
    }
}
int main(int argc, char* argv[])
{
    make_directory(argv[1]);
    return 0;
}