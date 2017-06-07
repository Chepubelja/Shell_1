//
// Created by paniv on 23.05.17.
//

#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;
static int f_flag = 0;
static int h_flag = 0;
void move_file_to_file(int argc,char *argv[]){
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "-f") == 0){
            f_flag = 1;
        } else if (strcmp(argv[i], "-h") == 0 || (strcmp(argv[i], "--help")) == 0){
            h_flag = 1;
        }
    }

    if (h_flag){
        cout << "mv [-h|--help] [-f] <oldfile> <newfile>\n"
                "mv [-h|--help] [-f] <oldfile1> <oldfile2> <oldfile3>.... <newdir>" << endl;
        exit(1);
    }
    if (f_flag){
        ifstream  src(argv[2], ios::binary);
        ofstream  dst(argv[3], ios::binary);
        dst << src.rdbuf();
        remove(argv[2]);
        cout << "Moved successfully" << endl;
    } else {
        string check;
        cout << "Do you really want to move file[Y or N] ?";
        cin >> check;
        if (check == "Y" || check == "y"){
            ifstream  src(argv[1], ios::binary);
            ofstream  dst(argv[2], ios::binary);
            dst << src.rdbuf();
            remove(argv[1]);
            cout << "Moved successfully" << endl;
        }
        else
        {
            exit(1);
        }
    }

}

int main(int argc, char *argv[]) {
    move_file_to_file(argc,argv);
    return 0;
}
