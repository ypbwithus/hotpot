#include "PlateActivator.h"
#include <QDebug>

void PlateActivator::start(ctkPluginContext* context)
{
    qDebug() << "PlateCTK start";

    plateImplSharePtr = std::make_shared<PlateImpl>(context);
    context->registerService<PlateService>(plateImplSharePtr.get());
    // 激活类里有一个独占智能指针,指向接口类【使用多态,指针都指向父类】,
    // 然后在start里new一个实现类,注册这个实现类为服务,功能是实现接口类的接口,
    // 然后将智能指针指向这个实现类。可以理解为以后向框架索取这个服务的时候,
    // 实际获取的就是这个new出来的实现类。如果不用智能指针,
    // 就需要在stop里手动delete这个实现类。

    // 每个插件都有自己的注册器Activator,功能节接口完成后,在插件启动时注册到ctk框架的服务中。
}

void PlateActivator::stop(ctkPluginContext* context)
{
    qDebug() << "PlateCTK stop";
    Q_UNUSED(context)
    //Q_UNUSED,如果一个函数的有些参数没有用到、某些变量只声明不使用，但是又不想编译器、编辑器报警报，其他没有什么实际性作用
}
