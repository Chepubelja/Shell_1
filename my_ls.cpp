#include <iostream>
#include <boost/filesystem.hpp>
#include <dirent.h>
#include <regex.h>
#include <boost/regex.hpp>
using namespace boost::filesystem;
using namespace std;
static string is_path;
static int is_long = 0;
static int is_help = 0;
static string is_sort;
static int is_reverse = 0;
static string is_mask;
static regex_t regex;
size_t size_of_directory(path Path){
    size_t size = 0;
    for(recursive_directory_iterator it(Path);
        it!=recursive_directory_iterator();
        ++it)
    {
        if(!is_directory(*it))
            size+=file_size(*it);
    }
    return size;

}

struct file_info{
    const char *name;
    string extension;
    size_t size;
    time_t time_of_modification;
};
//void print_ls_long(struct file_info *list_of_files,string is_mask){
//    if(is_mask.empty()) {
//        for (int i = 0; i < sizeof(list_of_files); i++) {
//            if (is_directory(list_of_files[i].name)) {
//                cout << "/" << list_of_files[i].name << " Is directory " << list_of_files[i].size << " "
//                     << ctime(&list_of_files[i].time_of_modification);
//            } else {
//                cout << list_of_files[i].name << " " << list_of_files[i].extension << " " << list_of_files[i].size
//                     << " "
//                     << ctime(&list_of_files[i].time_of_modification);
//            }
//        }
//    }else{
//        for (int i = 0; i < sizeof(list_of_files); i++) {
//            if(list_of_files[i].name.find(is_mask) != string::npos){
//                if (is_directory(list_of_files[i].name)) {
//                    cout << "/" << list_of_files[i].name << " Is directory " << list_of_files[i].size << " "
//                         << ctime(&list_of_files[i].time_of_modification);
//                } else {
//                    cout << list_of_files[i].name << " " << list_of_files[i].extension << " " << list_of_files[i].size
//                         << " "
//                         << ctime(&list_of_files[i].time_of_modification);
//                }
//            }
//        }
//    }
//}
void print_ls(struct file_info *list_of_files,string is_mask){
    int reg;
    if(is_mask.empty()) {
        for (int i = 0; i < sizeof(list_of_files); i++) {
            if (is_directory(list_of_files[i].name)) {
                cout << "/" << list_of_files[i].name << endl;
            } else {
                cout << list_of_files[i].name << endl;
            }
        }
    }else{
        for (int i = 0; i < sizeof(list_of_files); i++) {
            reg = regexec(&regex,list_of_files[i].name,0,NULL,0);
            cout << list_of_files[i].name << endl;
            if (!reg) {
                if (is_directory(list_of_files[i].name)) {
                    cout << "/" << list_of_files[i].name << endl;
                } else {
                    cout << list_of_files[i].name << endl;
                }
            }
        }
    }
}
int name_sort(const void *name1, const void *name2){
    const struct file_info *filename1 = (struct file_info*) name1;
    const struct file_info *filename2 = (struct file_info*) name2;
    return strcmp((filename1->name),(filename2->name));
}
int size_sort(const void *name1, const void *name2){
    const struct file_info *filename1 = (struct file_info*) name1;
    const struct file_info *filename2 = (struct file_info*) name2;
    return (filename1->size - filename2->size);
}
int time_sort(const void *name1, const void *name2){
    const struct file_info *filename1 = (struct file_info*) name1;
    const struct file_info *filename2 = (struct file_info*) name2;
    return (filename1->time_of_modification - filename2->time_of_modification);
}
int extention_sort(const void *name1, const void *name2){
    const struct file_info *filename1 = (struct file_info*) name1;
    const struct file_info *filename2 = (struct file_info*) name2;
    string ext1 = filename1->extension;
    string ext2 = filename2->extension;
    if (ext1.empty()){
        ext1 = "";
    }if (ext2.empty()){
        ext2 = "";
    }
    return strcmp(ext1.c_str(),ext2.c_str());
}
void reverseArray(file_info *arr, int start, int end)
{
    file_info* pBegin = arr + start;
    file_info* pEnd = arr + end;
    reverse(pBegin,pEnd);
}
void lsing(struct file_info *list_of_files){
    path full_path(current_path());
    DIR *dir;
    struct dirent *ent;
    int index = 0;
    if ((dir = opendir(full_path.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (!(strcmp(ent->d_name, "..") == 0 || strcmp(ent->d_name, ".") == 0)) {
                if (is_directory(ent->d_name)) {
                    list_of_files[index].name = ent->d_name;
                    list_of_files[index].extension = extension(ent->d_name);
                    list_of_files[index].size = size_of_directory(ent->d_name);
                    list_of_files[index].time_of_modification = last_write_time(ent->d_name);
                    index++;
                } else {
                    list_of_files[index].name = ent->d_name;
                    list_of_files[index].extension = extension(ent->d_name);
                    list_of_files[index].size = file_size(ent->d_name);
                    list_of_files[index].time_of_modification = last_write_time(ent->d_name);
                    index++;
                }
            }
        }
        closedir(dir);
    }
}
int main (int argc, char* argv[])
{
    struct file_info* list_of_files = (file_info *) malloc(256 * sizeof(file_info) );
    for (int i = 1; i < argc; i++){
        if (is_directory(argv[i])){
            is_path = string(argv[i]);
            cout << 1 << endl;
        } else if(strcmp(argv[i],"-l") == 0 ){
            is_long = 1;
            cout << 2 << endl;
        }else if(strcmp(argv[i],"-h") == 0 || strcmp(argv[i],"--help") == 0){
            is_help = 1;
            cout << 3 << endl;
        } else if(strcmp(argv[i],"-r") == 0 ){
            is_reverse = 1;
            cout << 4 << endl;
        } else if (strcmp("--sort=", string(argv[i]).substr(0,7).c_str()) == 0) {
            is_sort = string(argv[i]).substr(7).c_str();
            cout << 5 << endl;
        }else if(!regcomp(&regex, argv[i], 0)) {
            is_mask = string(argv[i]);
            cout << 6 << endl;
        } else {
            cout << "ls [path|mask] [-l] [-h|--help] [--sort=U|S|t|X] [-r] – вивести список файлів" << endl;
        }
    }
    if(is_help){
        cout << "ls [path|mask] [-l] [-h|--help] [--sort=U|S|t|X] [-r] – вивести список файлів" << endl;

    }else if (argc == 1){
        lsing(list_of_files);
        print_ls(list_of_files,"");
    } else {
        if (!is_path.empty()) {
            chdir(is_path.c_str());
        }
        lsing(list_of_files);
        if(!is_sort.empty()){
            if (strcmp(is_sort.c_str(),"N") == 0){
                //qsort(list_of_files,sizeof(list_of_files), sizeof(struct file_info),name_sort);
            }if(strcmp(is_sort.c_str(),"S") == 0){
                qsort(list_of_files,sizeof(list_of_files), sizeof(struct file_info),size_sort);
            }if(strcmp(is_sort.c_str(),"t") == 0) {
                qsort(list_of_files, sizeof(list_of_files), sizeof(struct file_info), time_sort);
            }if(strcmp(is_sort.c_str(),"X") == 0) {
                qsort(list_of_files, sizeof(list_of_files), sizeof(struct file_info), extention_sort);
            }else{
                cout << "ls [path|mask] [-l] [-h|--help] [--sort=U|S|t|X] [-r] – вивести список файлів" << endl;
                exit(1);
            }

        }else{
            //qsort(list_of_files,sizeof(list_of_files), sizeof(struct file_info),name_sort);
        }
        if(is_reverse){
            reverseArray(list_of_files,0,sizeof(list_of_files));
        }
        if(is_long){
            if(!is_mask.empty()){
                is_mask = is_mask.substr(1,is_mask.size() + 1);
                //print_ls_long(list_of_files,is_mask);
            }else {
                //print_ls_long(list_of_files,"");
            }
        }else {
            if(!is_mask.empty()){
                is_mask = is_mask.substr(1,is_mask.size() + 1);
                print_ls(list_of_files,is_mask);
            }else {
                print_ls(list_of_files,"");
            }
        }

    }
}