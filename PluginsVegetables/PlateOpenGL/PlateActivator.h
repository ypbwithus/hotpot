#ifndef __PLATECTIVATOR_H__
#define __PLATECTIVATOR_H__

#include <QObject>
#include "ctkPluginActivator.h"
#include "PlateImpl.h"
#include <thread>
#include <memory>
#include <logHelper.h>

using namespace std;

class PlateActivator : public QObject, public ctkPluginActivator
{
    Q_OBJECT
    Q_INTERFACES(ctkPluginActivator)
    Q_PLUGIN_METADATA(IID "PlateCTK")
    //向Qt的插件框架声明，希望将xxx插件放入到框架中。

public:
    void start(ctkPluginContext* context);
    void stop(ctkPluginContext* context);

    std::shared_ptr<PlateImpl> plateImplSharePtr;

};

#endif // Plate_ACTIVATOR_H
