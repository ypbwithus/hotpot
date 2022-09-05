#ifndef __PLATIMPL_H__
#define __PLATIMPL_H__

#include "PlateService.h"
#include <QObject>
#include <logHelper.h>
#include "OpenGLStart.h"

class ctkPluginContext;

class PlateImpl : public QObject, public PlateService
{
    Q_OBJECT
    Q_INTERFACES(PlateService)
    /*
    此宏与Q_DECLARE_INTERFACE宏配合使用。
    Q_DECLARE_INTERFACE：声明一个接口类
    Q_INTERFACES：当一个类继承这个接口类，表明需要实现这个接口类
    */
public:
    PlateImpl(ctkPluginContext *context);
    void sayHello() Q_DECL_OVERRIDE;
};

#endif // HELLO_IMPL_H
