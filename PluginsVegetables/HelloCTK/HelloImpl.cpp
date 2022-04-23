#include "HelloImpl.h"
#include <ctkPluginContext.h>
#include <QtDebug>

HelloImpl::HelloImpl(ctkPluginContext* context)
{
    qDebug() << "HelloImpl construct!";
}

void HelloImpl::sayHello()
{
    qDebug() << "Hello,CTK!";
}
