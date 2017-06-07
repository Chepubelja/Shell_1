//
// Created by paniv on 23.05.17.
//

#include <boost/lambda/lambda.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <boost/algorithm/string.hpp>
using namespace boost::filesystem;
using namespace std;

int main(int argc, char* argv[])
{
    static int f_flag = 0;
    static int h_flag = 0;
    static int R_flag = 0;
    char* directories[argc - 1];
    int index = 0;
    for (int j = 1; j < argc; ++j) {
        if (strcmp(argv[j], "-f") == 0) {
            f_flag = 1;
        } else if (strcmp(argv[j], "-h") == 0 || strcmp(argv[j], "--help") == 0) {
            h_flag = 1;
        } else if (strcmp(argv[j], "-R") == 0) {
            R_flag = 1;
        } else if (is_directory(argv[j]) || is_regular_file(argv[j])) {
            directories[index] = argv[j];
            index++;
        }
    }

    if (h_flag) {
        cout << "rm [-h|--help] [-f] [-R] <file1> <file2> <file3>";
        exit(1);
    }
    else if (f_flag) {
        for (int j = 0; j < index; ++j) {
            path p{directories[j]};
            string check;
            if (!is_directory(directories[j])) {
                if (exists(p))
                    remove(p);
                cout << "Removed successfully" << endl;
            }else{
                if(R_flag){
                    if (exists(p))
                        remove(p);
                    cout << "Removed successfully" << endl;
                }else{
                    cout << "You can only remove directories using -R flag!" << endl;
                }
            }
        }
    }else{
        for (int j = 0; j < index; ++j) {
            path p{directories[j]};
            if(!is_directory(directories[j])){
                string check;
                cout << "Do you really want to delete it ? [Y or N] : ";
                cin >> check;
                if (check == "Y" || check == "y")
                    if (exists(p))
                        remove(p);
                cout << "Removed successfully" << endl;
            }else {
                if (R_flag) {
                    string check;
                    cout << "Do you really want to delete it ? [Y or N] : ";
                    cin >> check;
                    if (check == "Y" || check == "y")
                        if (exists(p))
                            remove(p);
                    cout << "Removed successfully" << endl;
                }else{
                    cout << "You can only remove directories using -R flag!" << endl;
                }

            }
        }
    }
    return 0;
}
