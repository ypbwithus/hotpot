#ifndef GREET_SERVICE_H
#define GREET_SERVICE_H

#include <QtPlugin>

class HelloService
{
public:
    virtual ~HelloService() {}
    virtual void sayHello() = 0;
};

#define HelloService_iid "org.commontk.service.greet.HelloService"
Q_DECLARE_INTERFACE(HelloService, HelloService_iid)

class ByeService
{
public:
    virtual ~ByeService() {}
    virtual void sayBye() = 0;
};

#define ByeService_iid "org.commontk.service.greet.ByeService"
Q_DECLARE_INTERFACE(ByeService, ByeService_iid)

#endif // GREET_SERVICE_H
