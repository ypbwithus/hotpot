#include <QCoreApplication>
#include <QDirIterator>
#include <QtDebug>
#include <ctkPluginFrameworkFactory.h>
#include <ctkPluginFrameworkLauncher.h>
#include <ctkPluginFramework.h>
#include <ctkPluginException.h>
#include <ctkPluginContext.h>
// #include "../PluginsVegetables/HelloCTK/HelloService.h"
#include "../PluginsVegetables/greet/greet_service.h"
#include "../PluginsVegetables/Welcome/WelcomeService/welcome_service.h"
#include "../PluginsVegetables/RequirePlugin/PluginA/plugin_a_service.h"
#include "../PluginsVegetables/RequirePlugin/PluginB/plugin_b_service.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // app.setApplicationName("SampleCTK"); //给框架创建名称，Linux下没有会报错
    // ctkPluginFrameworkFactory frameWorkFactory;
    // QSharedPointer<ctkPluginFramework> framework = frameWorkFactory.getFramework();
    // try
    // {
    //     // 初始化并启动插件框架
    //     framework->init();
    //     framework->start();
    //     qDebug() << "CTK Plugin Framework start ...";
    // }
    // catch (const ctkPluginException &e)
    // {
    //     qDebug() << "Failed to initialize the plugin framework: " << e.what();
    //     qDebug() << e.message() << e.getType();
    //     return -1;
    // }

    // // 获取插件上下文
    // ctkPluginContext *context = framework->getPluginContext();

    // // 获取插件所在位置
    // QString path = QCoreApplication::applicationDirPath() + "/plugins";
    // qDebug() << __TIME__ << __FILE__ << __LINE__ << ":" << path;

    // // 遍历路径下的所有插件
    // QDirIterator itPlugin(path, QStringList() << "*.dll"
    //                                           << "*.so",
    //                       QDir::Files);

    // while (itPlugin.hasNext())
    // {
    //     QString strPlugin = itPlugin.next();
    //     try
    //     {
    //         // 安装插件
    //         QSharedPointer<ctkPlugin> plugin = context->installPlugin(QUrl::fromLocalFile(strPlugin));
    //         // 启动插件
    //         plugin->start(ctkPlugin::START_TRANSIENT);
    //         qDebug() << "Plugin start ...";
    //     }
    //     catch (const ctkPluginException &e)
    //     {
    //         qDebug() << "Failed to install plugin" << e.what();
    //         return -1;
    //     }
    // }

    // 0, 一个插件一服务HelloCTK : HelloService
    // 1, 一个插件多个服务greet : ByeService HelloService
    // 2, 多个插件一个服务WelcomeService : 服务的name不一样

    // 主函数框架及插件加载完成后，即可调用插件接口
    // 获取服务引用
    // 0, ------------------------------一个插件一服务HelloCTK : HelloService---------------------------------------
    // 1, ------------------------------一个插件多个服务greet : ByeService HelloService---------------------------------------
    // ctkServiceReference reference = context->getServiceReference<HelloService>();
    // if (reference)
    // {
    //     // 获取指定 ctkServiceReference 引用的服务对象,可以直接调用到服务类的引用
    //     // HelloService* service = qobject_cast<HelloService*>(context->getService(reference));
    //     HelloService *service = qobject_cast<HelloService *>(context->getService(reference));
    //     if (service != Q_NULLPTR)
    //     {
    //         // 调用服务
    //         service->sayHello();
    //     }
    // }

    // reference = context->getServiceReference<ByeService>();
    // if (reference)
    // {
    //     ByeService *service = qobject_cast<ByeService *>(context->getService(reference));
    //     if (service != Q_NULLPTR)
    //         service->sayBye();
    // }

    // --------------------------------------2 多个插件一个服务WelcomeService : 服务的name不一样---------------------------------------
    //    qDebug() << "********************";

    //    // 1. 获取所有服务
    //    QList<ctkServiceReference> refs = context->getServiceReferences<WelcomeService>();
    //    foreach (ctkServiceReference ref, refs)
    //    {
    //        if (ref)
    //        {
    //            qDebug() << "Name:" << ref.getProperty("name").toString()
    //                     << "Service ranking:" << ref.getProperty(ctkPluginConstants::SERVICE_RANKING).toLongLong()
    //                     << "Service id:" << ref.getProperty(ctkPluginConstants::SERVICE_ID).toLongLong();
    //            WelcomeService *service = qobject_cast<WelcomeService *>(context->getService(ref));
    //            if (service != Q_NULLPTR)
    //                service->welcome();
    //        }
    //    }

    //    qDebug() << "********************";

    //    // 2. 使用过滤表达式，获取感兴趣的服务
    //    refs = context->getServiceReferences<WelcomeService>("(&(name=CTK))");
    //    foreach (ctkServiceReference ref, refs)
    //    {
    //        if (ref)
    //        {
    //            WelcomeService *service = qobject_cast<WelcomeService *>(context->getService(ref));
    //            if (service != Q_NULLPTR)
    //                service->welcome();
    //        }
    //    }

    //    qDebug() << "********************";

    //    // 3. 获取某一个服务（由 Service Ranking 和 Service ID 决定） Qt 的级别高吗？
    //    ctkServiceReference ref = context->getServiceReference<WelcomeService>();
    //    if (ref)
    //    {
    //        WelcomeService *service = qobject_cast<WelcomeService *>(context->getService(ref));
    //        if (service != Q_NULLPTR)
    //            service->welcome();
    //    }

    //---------------------发布订阅消息----------------------------------------------
    // 获取插件所在位置
    // 在插件的搜索路径列表中添加一条路径
    ctkPluginFrameworkLauncher::addSearchPath("../../../bin/plugins");
    // 设置并启动 CTK 插件框架
    ctkPluginFrameworkLauncher::start("org.commontk.eventadmin");
    // 获取插件上下文
    ctkPluginContext *context = ctkPluginFrameworkLauncher::getPluginContext();

    QString path = QCoreApplication::applicationDirPath() + "/plugins";

    // ------------------------Event 发布和订阅-----------------------------------------------------------
    // // 启动插件 BlogEventHandler
    // try
    // {
    //     QSharedPointer<ctkPlugin> plugin = context->installPlugin(QUrl::fromLocalFile(path + "/BlogEventHandler.dll"));
    //     plugin->start();
    //     qDebug() << "BlogEventHandler start ...";
    // }
    // catch (const ctkPluginException &e)
    // {
    //     qDebug() << "Failed to start BlogEventHandler" << e.what();
    // }

    // //启动插件 BlogManager
    // try
    // {
    //     QSharedPointer<ctkPlugin> plugin = context->installPlugin(QUrl::fromLocalFile(path + "/BlogManager.dll"));
    //     plugin->start();
    //     qDebug() << "BlogManager start ...";
    // }
    // catch (const ctkPluginException &e)
    // {
    //     qDebug() << "Failed to start BlogManager" << e.what();
    // }

    // 启动插件 BlogEventHandlerUsingSlots
    try {
        QSharedPointer<ctkPlugin> plugin = context->installPlugin(QUrl::fromLocalFile(path + "/BlogEventHandlerUsingSlots.dll"));
        plugin->start();
        qDebug() << "BlogEventHandlerUsingSlots start ...";
    } catch (const ctkPluginException &e) {
        qDebug() << "Failed to start BlogEventHandlerUsingSlots" << e.what();
    }

    // 启动插件 BlogManagerUsingSignals
    try {
        QSharedPointer<ctkPlugin> plugin = context->installPlugin(QUrl::fromLocalFile(path + "/BlogManagerUsingSignals.dll"));
        plugin->start();
        qDebug() << "BlogManagerUsingSignals start ...";
    } catch (const ctkPluginException &e) {
        qDebug() << "Failed to start BlogManagerUsingSignals" << e.what();
    }

    // 停止插件
    ctkPluginFrameworkLauncher::stop();

    // ----------------------------------互相依赖-----------------------------------
    // // 启动插件 A
    // try
    // {
    //     QSharedPointer<ctkPlugin> plugin = context->installPlugin(QUrl::fromLocalFile(path + "/PluginA.dll"));
    //     plugin->start();
    //     qDebug() << "PluginA start ...";
    // }
    // catch (const ctkPluginException &e)
    // {
    //     qDebug() << "Failed to start PluginA" << e.what();
    // }

    // // 启动插件 B
    // try
    // {
    //     QSharedPointer<ctkPlugin> plugin = context->installPlugin(QUrl::fromLocalFile(path + "/PluginB.dll"));
    //     plugin->start();
    //     qDebug() << "PluginB start ...";
    // }
    // catch (const ctkPluginException &e)
    // {
    //     qDebug() << "Failed to start PluginB" << e.what();
    // }

    // // 获取服务引用
    // ctkServiceReference reference = context->getServiceReference<PluginAService>();
    // if (reference)
    // {
    //     // 获取指定 ctkServiceReference 引用的服务对象
    //     PluginAService *service = qobject_cast<PluginAService *>(context->getService(reference));
    //     if (service != Q_NULLPTR)
    //     {
    //         // 调用服务
    //         service->doSomething();
    //     }
    // }

    // reference = context->getServiceReference<PluginBService>();
    // if (reference)
    // {
    //     // 获取指定 ctkServiceReference 引用的服务对象
    //     PluginBService *service = qobject_cast<PluginBService *>(context->getService(reference));
    //     if (service != Q_NULLPTR)
    //     {
    //         // 调用服务
    //         service->doSomething();
    //     }
    // }

    return app.exec();
}
