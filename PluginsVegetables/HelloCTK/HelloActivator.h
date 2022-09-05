#ifndef HELLO_ACTIVATOR_H
#define HELLO_ACTIVATOR_H

#include <QObject>
#include "ctkPluginActivator.h"
#include "HelloImpl.h"
#include <thread>
#include <memory>

using namespace std;

class HelloActivator : public QObject, public ctkPluginActivator
{
    Q_OBJECT
    Q_INTERFACES(ctkPluginActivator)
    Q_PLUGIN_METADATA(IID "HELLO_CTK")
    //向Qt的插件框架声明，希望将xxx插件放入到框架中。

public:
    void start(ctkPluginContext* context);
    void stop(ctkPluginContext* context);

    std::shared_ptr<HelloImpl> helloImplSharePtr;

};

#endif // HELLO_ACTIVATOR_H
