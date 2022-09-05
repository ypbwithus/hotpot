#ifndef __THREAD_BASE_H__
#define __THREAD_BASE_H__
 
// 重构思路
// 现在是采用的继承,继承用在线程上有缺陷，不够灵活
// 如果可以将线程函数传入就可以灵活应用其实这就够了，就可以在一个里类中定义定义多个线程，而这个线程函数属于自定义的类中
 
#include <pthread.h>
#include <iostream>
#include <signal.h>
#include <glog/logging.h>

using namespace std;

typedef void (*ThreadFunType)(void * _Pthis); 

class ThreadBase
{
private:
    pthread_t m_tid;
    bool      m_isAlive;
 
private:
    static void* start_func(void* arg);
 
public:
    int start(ThreadFunType run,void * _Pthis);
    int join();
    int quit();
    int detach();
 
    pthread_t getTid();
    bool isAlive();
 
    void *Pthis;
    void (*run)(void * _Pthis);
    // virtual void run() = 0;
    virtual ~ThreadBase();
};

#endif

