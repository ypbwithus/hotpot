#include <QCoreApplication>
#include <QDirIterator>
#include <QtDebug>
#include <ctkPluginFrameworkFactory.h>
#include <ctkPluginFramework.h>
#include <ctkPluginException.h>
#include <ctkPluginContext.h>
// #include "../PluginsVegetables/HelloCTK/HelloService.h"
#include "../PluginsVegetables/greet/greet_service.h"
#include "../PluginsVegetables/WelcomeService/welcome_service.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName("SampleCTK"); //给框架创建名称，Linux下没有会报错
    ctkPluginFrameworkFactory frameWorkFactory;
    QSharedPointer<ctkPluginFramework> framework = frameWorkFactory.getFramework();
    try
    {
        // 初始化并启动插件框架
        framework->init();
        framework->start();
        qDebug() << "CTK Plugin Framework start ...";
    }
    catch (const ctkPluginException &e)
    {
        qDebug() << "Failed to initialize the plugin framework: " << e.what();
        qDebug() << e.message() << e.getType();
        return -1;
    }

    // 获取插件上下文
    ctkPluginContext *context = framework->getPluginContext();

    // 获取插件所在位置
    QString path = QCoreApplication::applicationDirPath() + "/plugins";
    qDebug() << __TIME__ << __FILE__ << __LINE__ << ":" << path;

    // 遍历路径下的所有插件
    QDirIterator itPlugin(path, QStringList() << "*.dll"
                                              << "*.so",
                          QDir::Files);

    while (itPlugin.hasNext())
    {
        QString strPlugin = itPlugin.next();
        try
        {
            // 安装插件
            QSharedPointer<ctkPlugin> plugin = context->installPlugin(QUrl::fromLocalFile(strPlugin));
            // 启动插件
            plugin->start(ctkPlugin::START_TRANSIENT);
            qDebug() << "Plugin start ...";
        }
        catch (const ctkPluginException &e)
        {
            qDebug() << "Failed to install plugin" << e.what();
            return -1;
        }
    }

    // 0, 一个插件一服务HelloCTK : HelloService
    // 1, 一个插件多个服务greet : ByeService HelloService
    // 2, 多个插件一个服务greet : ByeService HelloService

    // 主函数框架及插件加载完成后，即可调用插件接口
    // 获取服务引用
    // 0, 一个插件一服务HelloCTK : HelloService
    // 1, 一个插件多个服务greet : ByeService HelloService
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

    // 2 多个插件一个服务greet : ByeService HelloService
    qDebug() << "********************";

    // 1. 获取所有服务
    QList<ctkServiceReference> refs = context->getServiceReferences<WelcomeService>();
    foreach (ctkServiceReference ref, refs)
    {
        if (ref)
        {
            qDebug() << "Name:" << ref.getProperty("name").toString()
                     << "Service ranking:" << ref.getProperty(ctkPluginConstants::SERVICE_RANKING).toLongLong()
                     << "Service id:" << ref.getProperty(ctkPluginConstants::SERVICE_ID).toLongLong();
            WelcomeService *service = qobject_cast<WelcomeService *>(context->getService(ref));
            if (service != Q_NULLPTR)
                service->welcome();
        }
    }

    qDebug() << "********************";

    // 2. 使用过滤表达式，获取感兴趣的服务
    refs = context->getServiceReferences<WelcomeService>("(&(name=CTK))");
    foreach (ctkServiceReference ref, refs)
    {
        if (ref)
        {
            WelcomeService *service = qobject_cast<WelcomeService *>(context->getService(ref));
            if (service != Q_NULLPTR)
                service->welcome();
        }
    }

    qDebug() << "********************";

    // 3. 获取某一个服务（由 Service Ranking 和 Service ID 决定） Qt 的级别高吗？
    ctkServiceReference ref = context->getServiceReference<WelcomeService>();
    if (ref)
    {
        WelcomeService *service = qobject_cast<WelcomeService *>(context->getService(ref));
        if (service != Q_NULLPTR)
            service->welcome();
    }

    return app.exec();
}
