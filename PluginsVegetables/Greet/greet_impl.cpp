#include "greet_impl.h"
#include <QtDebug>

GreetImpl::GreetImpl()
{

}

void GreetImpl::sayHello()
{
    qDebug() << "GreetImpl Hello,CTK!";
}

void GreetImpl::sayBye()
{
    qDebug() << "GreetImpl Bye,CTK!";
}
