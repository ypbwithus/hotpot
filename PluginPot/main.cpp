#include <QCoreApplication>
#include <QDirIterator>
#include <QtDebug>
#include <ctkPluginFrameworkFactory.h>
#include <ctkPluginFrameworkLauncher.h>
#include <ctkPluginFramework.h>
#include <ctkPluginException.h>
#include <ctkPluginContext.h>
#include "../PluginsVegetables/HelloCTK/HelloService.h"
#include "logHelper.h"
#include "spdlogHelper.h"
#include "PluginsVegetables/PlateOpenGL/OpenGLStart/OpenGLStart.h"
#include "spdlogHelper.h"

namespace SharedLibPart
{
    // 可以是一个类
    __declspec(dllimport) void Print(); // 导入动态链接库中的全局变量方面起作用
}

using namespace std;

std::mutex main_mutex_locker;
std::condition_variable main_cond_locker;

int main(int argc, char *argv[])
{
    // 初始化LOG
    // spd log
    spdInit();
    SPDINFO(" :) App start !");

    // glog
    // logHelper::GetInstance(argv);
    // LOG(INFO) << " :) App start !";

    // OpenGLStart::GetInstance();

    SharedLibPart::Print();

    // 挂起
    std::unique_lock<std::mutex> lk(main_mutex_locker);
    main_cond_locker.wait(lk);
}
