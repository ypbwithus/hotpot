#include <logHelper.h>

bool logHelper::debug = 1;

logHelper *logHelper::GetInstance(char *argv[])
{
    // cout << "Get Instance of logHelper" << endl;

    //------------------------------配置glog---------------------------------------------------------------

    // 使用C++17新特性
    fs::create_directories("logs");

    google::InitGoogleLogging(argv[0]);

    // google::ShutdownGoogleLogging();
    FLAGS_log_dir = "logs"; //命名方法和gflags类似

    // FLAGS_logtostderr = true; //设置日志消息是否转到标准输出而不是日志文件

    FLAGS_alsologtostderr = true; //设置日志消息除了日志文件之外是否去标准输出

    FLAGS_colorlogtostderr = true; //设置记录到标准输出的颜色消息（如果终端支持）
    //一般是从ERROR才有颜色，如果INFO有颜色可以添加：

    FLAGS_stderrthreshold = google::GLOG_ERROR;

    FLAGS_log_prefix = true; //设置日志前缀是否应该添加到每行输出

    FLAGS_logbufsecs = 0; //设置可以缓冲日志的最大秒数，0指实时输出

    google::SetLogDestination(google::GLOG_FATAL, "./logs/log_FATAL_");     // 设置 google::FATAL 级别的日志存储路径和文件名前缀
    google::SetLogDestination(google::GLOG_ERROR, "./logs/log_ERROR_");     //设置 google::ERROR 级别的日志存储路径和文件名前缀
    google::SetLogDestination(google::GLOG_WARNING, "./logs/log_WARNING_"); //设置 google::WARNING 级别的日志存储路径和文件名前缀
    google::SetLogDestination(google::GLOG_INFO, "./logs/log_INFO_");       //设置 google::INFO 级别的日志存储路径和文件名前缀

    FLAGS_max_log_size = 10; //设置最大日志文件大小（以MB为单位）

    FLAGS_stop_logging_if_full_disk = true; //设置是否在磁盘已满时避免日志记录到磁盘

    // LOG(INFO) << ":) 系统启动 ！"; //输出一个Info日志

    // LOG(INFO) << "info test";		//输出一个Info日志
    // LOG(WARNING) << "warning test"; //输出一个Warning日志
    // LOG(ERROR) << "error test";		//输出一个Error日志
    // LOG(FATAL) << "fatal test";		//输出一个Fatal日志，这是最严重的日志并且输出之后会中止程序

    //-------------------------------------------------------------------------------------------------------

    static logHelper inst;

    return &inst;
}

logHelper::logHelper()
{
    LOG(INFO) << "In Constructor of logHelper" << endl;

    // delThread.start(this->delThreadFun, this);
    // delThread.detach();

    delThread = new thread(delThreadFun, this);
    delThread->detach();
}

void logHelper::delThreadFun(void *_Pthis)
{
    while (1)
    {
        logHelper::RotatingLogFiles(10, 10);

        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}

struct filePathCompare_
{
    bool operator()(string i, string j)
    {
        size_t a = 0;
        size_t b = 0;

        string regex_str("\\d{8}-\\d{6}");
        regex pattern(regex_str, regex::icase);

        // logs\20201212162018.247108.log
        {
            smatch results;
            if (regex_search(i, results, pattern))
            {
                smatch::iterator itPattern = results.begin();
                int i = 0;
                for (; itPattern != results.end(); ++itPattern, ++i)
                {
                    string dateNumStr = itPattern->str().substr(0, 8) + itPattern->str().substr(9, 14);
                    a = atoll(dateNumStr.c_str());
                    // LOG(INFO) << i;
                }
            }
        }

        {
            smatch results;
            if (regex_search(j, results, pattern))
            {
                smatch::iterator itPattern = results.begin();
                int i = 0;
                for (; itPattern != results.end(); ++itPattern, ++i)
                {
                    string dateNumStr = itPattern->str().substr(0, 8) + itPattern->str().substr(9, 14);
                    b = atoll(dateNumStr.c_str());
                    // LOG(INFO) << b;
                }
            }
        }

        return (a > b);
    }
} filePathCompare;

void logHelper::RotatingLogFiles(unsigned int filesNum, double filesSize)
{
    // time_t currentTime_t;
    // static unsigned long currentTime = 0, lastTime = 0;
    // currentTime = time(&currentTime_t);

    // if ((currentTime - lastTime) > 1)
    {
        // LOG(INFO) << currentTime;
        // LOG(INFO) << lastTime;

        const string filesPath = "logs";
        vector<string> files;

        vector<string> INFOFiles;

        vector<string> WARNINGFiles;

        vector<string> ERRORFiles;
        // vector<string> INFOFiles;
        // vector<string> WARNINGFiles;
        // vector<string> ERRORFiles;

        // string earliestINFOFile;
        // time_t earliestINFOTime = 0;
        // unsigned char INFOFileCnt = 0;
        // string earliestWARNINGFile;
        // time_t earliestWARNINGTime = 0;
        // unsigned char WARNINGFileCnt = 0;
        // string earliestERRORFile;
        // time_t earliestERRORTime = 0;
        // unsigned char ERRORFileCnt = 0;

        // unsigned long INFOFileSize = 0;
        // unsigned long WARNINGFileSize = 0;
        // unsigned long ERRORFileSize = 0;

        // //  A2tpumain.FriendlyARM.root.log.ERROR.20190815-155801.18560
        // string regex_str("\\d{8}-\\d{6}");
        // regex pattern(regex_str, regex::icase);

        // dirHelper::getAllFiles(files, filesPath);

        for (auto &p : fs::directory_iterator("logs"))
        {
            files.push_back(p.path().string());
            // LOG(INFO) << p.path() << '\n';
        }

        for (auto &itFiles : files)
        {
            // LOG(INFO) << itFiles;

            if (itFiles.find("INFO") != std::string::npos)
            {
                INFOFiles.push_back(itFiles);
            }

            if (itFiles.find("WARNING") != std::string::npos)
            {
                WARNINGFiles.push_back(itFiles);
            }

            if (itFiles.find("ERROR") != std::string::npos)
            {
                ERRORFiles.push_back(itFiles);
            }
        }

        std::sort(WARNINGFiles.begin(), WARNINGFiles.end(), filePathCompare);
        std::sort(ERRORFiles.begin(), ERRORFiles.end(), filePathCompare);
        std::sort(INFOFiles.begin(), INFOFiles.end(), filePathCompare);

        for (int i = 0; i < INFOFiles.size(); i++)
        {
            // cout << i << ":" << INFOFiles[i] << endl;
            // index = iterator_to_index(a, it);
            if (i >= filesNum)
            {
                remove(INFOFiles[i].c_str());
            }
        }

        for (int i = 0; i < WARNINGFiles.size(); i++)
        {
            // cout << i << ":" << WARNINGFiles[i] << endl;
            // index = iterator_to_index(a, it);
            if (i >= filesNum)
            {
                remove(WARNINGFiles[i].c_str());
            }
        }

        for (int i = 0; i < ERRORFiles.size(); i++)
        {
            // cout << i << ":" << ERRORFiles[i] << endl;
            // index = iterator_to_index(a, it);
            if (i >= filesNum)
            {
                remove(ERRORFiles[i].c_str());
            }
        }

        // lastTime = currentTime;
    }
    // }
}

string logHelper::printfLog(const int level, const char *format, ...)
{
    va_list ap;

    va_start(ap, format);

    vector<char> printfbuf(1024);

    int ret;

    while ((ret = vsnprintf(&printfbuf[0], printfbuf.size(), format, ap)) == -1)
    {
        printfbuf.resize(printfbuf.size() * 2);
    }

    va_end(ap);

    // 结尾不是NULL，则截断

    if (ret == static_cast<int>(printfbuf.size()))
    {
        printfbuf[printfbuf.size() - 1] = '\0';
    }

    string printfbufStr(&printfbuf[0]);

    // if (level == INFO)
    //     LOG(INFO) << printfbufStr;
    // if (level == WARNING)
    //     LOG(WARNING) << printfbufStr;
    // if (level == ERROR)
    //     LOG(ERROR) << printfbufStr;
    // if (level == FATAL)
    //     LOG(FATAL) << printfbufStr;

    return printfbufStr;
}
