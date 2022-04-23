#ifndef HELLO_IMPL_H
#define HELLO_IMPL_H

#include "HelloService.h"
#include <QObject>

class ctkPluginContext;

class HelloImpl : public QObject, public HelloService
{
    Q_OBJECT
    Q_INTERFACES(HelloService)
    /*
    此宏与Q_DECLARE_INTERFACE宏配合使用。
    Q_DECLARE_INTERFACE：声明一个接口类
    Q_INTERFACES：当一个类继承这个接口类，表明需要实现这个接口类
    */
public:
    HelloImpl(ctkPluginContext *context);
    void sayHello() Q_DECL_OVERRIDE;
};

#endif // HELLO_IMPL_H
