
#ifndef ___DIRHELPER_H___
#define ___DIRHELPER_H___

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>    // std::sort
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/statfs.h> 

using namespace std;

class dirHelper
{
public:
    dirHelper();
    ~dirHelper() { cout << "In Destructor of dirHelper" << endl; }

    static void getAllFiles(vector<string> & files,const string cate_dir);

    static string getFreediskMb(string Path);

};

#endif
