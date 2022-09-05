#include <dirHelper.h>

void dirHelper::getAllFiles(vector<string> & files , const string cate_dir)
{
// #ifdef WIN32
//     _finddata_t file;
//     long lf;
//     //输入文件夹路径
//     if ((lf = _findfirst(cate_dir.c_str(), &file)) == -1)
//     {
//         cout << cate_dir << " not found!!!" << endl;
//     }
//     else
//     {
//         while (_findnext(lf, &file) == 0)
//         {
//             //输出文件名
//             //cout<<file.name<<endl;
//             if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0)
//                 continue;
//             files.push_back(file.name);
//         }
//     }
//     _findclose(lf);
// #endif

    DIR *dir;
    struct dirent *ptr;

    if ((dir = opendir(cate_dir.c_str())) == NULL)
    {
        perror("Open dir error...");
        exit(1);
    }

    while ((ptr = readdir(dir)) != NULL)
    {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0) ///current dir OR parrent dir
            continue;
        else if (ptr->d_type == 8) ///file
            files.push_back(ptr->d_name);
        else if (ptr->d_type == 10) ///link file
            continue;
        else if (ptr->d_type == 4) ///dir
        {
            // files.push_back(ptr->d_name);
            getAllFiles(files , ptr->d_name);
           
        }
    }

    closedir(dir);

    //排序，按从小到大排序
    //  std::sort (files.begin(), files.end());
}

string dirHelper::getFreediskMb(string Path)
{
    struct statfs diskInfo;
    statfs(Path.c_str(), &diskInfo);
    unsigned long long totalBlocks = diskInfo.f_bsize;
    unsigned long long totalSize = totalBlocks * diskInfo.f_blocks;
    size_t mbTotalsize = totalSize >> 20;
    unsigned long long freeDisk = diskInfo.f_bfree * totalBlocks;
    size_t mbFreedisk = freeDisk >> 20;
    //    printf ("%s  total=%dMB, free=%dMB\n",savePath.c_str(), mbTotalsize, mbFreedisk);

    return to_string(mbFreedisk);
}