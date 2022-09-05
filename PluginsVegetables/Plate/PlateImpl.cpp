#include "PlateImpl.h"
#include <ctkPluginContext.h>
#include <QtDebug>

PlateImpl::PlateImpl(ctkPluginContext* context)
{
    qDebug() << "PlateImpl construct!";
}

void PlateImpl::sayHello()
{
    qDebug() << "Plate,CTK!";
}
