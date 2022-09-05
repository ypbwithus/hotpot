#include "PlateImpl.h"
#include <ctkPluginContext.h>
#include <QtDebug>

PlateImpl::PlateImpl(ctkPluginContext *context)
{
    LOG(INFO) << "PlateImpl construct!";

    OpenGLStart::GetInstance();

}

void PlateImpl::sayHello()
{
    LOG(INFO) << "Plate,CTK!";
}
