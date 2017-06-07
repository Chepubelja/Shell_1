#include <boost/lambda/lambda.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <sys/wait.h>
#include <fstream>
#include <string>
#define BOOST_NO_CXX11_SCOPED_ENUMS
#undef BOOST_NO_CXX11_SCOPED_ENUMS

using namespace std;
using namespace boost::filesystem;
int eternal_functions(char * argv[]) {
    pid_t ChildPID;
    int exit_code;
    switch (ChildPID = fork()) {
        case -1 :
            cout << "ETERNAL FUNCTION PID ERROR" << endl;
        case 0:
            exit_code = execvp(argv[0], argv);
            cout << "Failed!: " << strerror(errno) << endl;
            return exit_code;
        default:
            if(wait(NULL) == -1){
                printf("%s \n","Error");
            }
    }
}

void func_cd(int size_of, char *commands[]){
    if (size_of > 2) {
        cout << "To much arguments" << endl;
    }
    else if (size_of != 1) {
        cout << commands[1] << endl;
        if (strcmp(commands[1],"-h") == 0 || strcmp(commands[1],"--help") == 0) {
            cout << "cd <path> [-h|--help]  -- перейти до шляху <path> " << endl;
        }
        else {
            chdir(commands[1]);
        }
    }
    else {
        cout << "We need at least 1 argument" << endl;
    }
}

void func_pwd(int size_of, char *commands[]){
    if (size_of > 2) {
        cout << "To much arguments" << endl;
    } else if (size_of != 1) {
        if (strcmp(commands[1], "-h") == 0 || strcmp(commands[1], "--help") ==0) {
            cout << "pwd [-h|--help] – вивести поточний шлях" << endl;
        } else {
            cout << "Incorrect command" << endl;
        }
    } else {
        char cwd[1024];
        cout << getcwd(cwd, sizeof(cwd)) << endl;
    }
}

void func_exit(int size_of, char *commands[]){
    if (size_of > 2) {
        cout << "To much arguments" << endl;
    } else if (size_of != 1) {
        if (strcmp(commands[1], "-h") == 0 || strcmp(commands[1], "--help") == 0) {
            cout << "exit [код завершення] [-h|--help]  – вийти " << endl;
        } else {
            cout << "Incorrect command" << endl;
        }
    }
    else {
        exit(1);
    }
}

int main() {
    char path_str[1024] = "PATH=";
    char *original_path;
    original_path = getcwd(NULL, 1024);
    strcat(path_str,original_path);
    putenv(path_str);
    while (1) {
        string command;
        vector<string> strings;
        path full_path(current_path());
        string path = full_path.string();
        path = path.substr(0, path.length());
        cout << path << "$ ";
        getline(cin, command);
        split(strings, command, boost::is_any_of(" "));
        int size_of = strings.size();
        char *commands[strings.size() + 1];
        for (size_t i = 0; i < strings.size(); ++i)
            commands[i] = const_cast<char *>(strings[i].c_str());
        commands[strings.size()] = NULL;
        if (strcmp(commands[0], "cd") == 0) {
            func_cd(size_of, commands);
        }
        else if (strcmp(commands[0], "pwd") == 0) {
            func_pwd(size_of, commands);
        }
        else if (strcmp(commands[0],"exit") == 0) {
            func_exit(size_of,commands);
        }
        else{
            eternal_functions(commands);
        }
    }

}
