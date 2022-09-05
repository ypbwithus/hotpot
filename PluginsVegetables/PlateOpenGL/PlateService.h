#ifndef __PLATESERVICE_H__
#define __PLATESERVICE_H__

#include <QtPlugin>

// 编写插件主要有3个步骤：接口类、实现类、激活类。
// 不在实现类的构造函数里注册服务，降低耦合性，接口类就只做接口声明，实现类就只实现接口，激活类就负责将服务整合到ctk框架中。

class PlateService
{
public:
    virtual ~PlateService() {}
    virtual void sayHello() = 0;
};

#define PlateService_iid "org.commontk.service.Plate.PlateService"
Q_DECLARE_INTERFACE(PlateService, PlateService_iid)

//此宏将当前这个接口类声明为接口，后面的一长串就是这个接口的唯一标识。

#endif // HELLO_SERVICE_H
