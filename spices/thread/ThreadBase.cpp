#include "ThreadBase.h"

void *ThreadBase::start_func(void *arg)
{
    ThreadBase *ptr = (ThreadBase *)arg;
    (*ptr->run)(ptr->Pthis);

    // ptr->detach();

    return NULL;
}

int ThreadBase::start(ThreadFunType _run, void *_Pthis)
{
    //  LOG(INFO) << "Start a new thread" << endl;

    if (_run != NULL)
    {
        this->run = _run;
    }
    else
    {
        LOG(ERROR) << "Thread function is Error !" << endl;
        return -1;
    }

    this->Pthis = _Pthis;

    if (pthread_create(&m_tid, NULL, start_func, (void *)this) != 0)
    {
        LOG(ERROR) << "Start a new thread failed!" << endl;
        return -1;
    }

    //  LOG(INFO) << "Start a new thread success! tid =" << m_tid << endl;

    m_isAlive = true;
    return 0;
}

int ThreadBase::join()
{
    int ret = -1;
    // LOG(INFO) << "Join the thread tid=" << m_tid << endl;

    if (isAlive())
    {
        ret = pthread_join(m_tid, NULL);

        if (ret != 0)
            LOG(ERROR) << "Join the thread fail tid=" << m_tid << endl;
        // else
        // LOG(INFO) << "Join the thread success tid=" << m_tid << endl;
    }
    else
    {
        LOG(WARNING) << "Thread is not alive !" << endl;
        return ret;
    }

    return ret;
}

int ThreadBase::detach()
{
    int ret = -1;
    // LOG(INFO) << "detach the thread tid=" << m_tid << endl;

    if (isAlive())
    {
        ret = pthread_detach(m_tid);

        if (ret != 0)
            LOG(ERROR) << "detach the thread fail tid=" << m_tid << endl;
        // else
        // LOG(INFO) << "detach the thread success tid=" << m_tid << endl;
    }
    else
    {
        LOG(WARNING) << "Thread is not alive !" << endl;
        return ret;
    }

    return ret;
}

int ThreadBase::quit()
{
    // LOG(INFO) << "Quit the thread tid=" << m_tid << endl;
    m_isAlive = false;
    return 0;
}

pthread_t ThreadBase::getTid()
{
    return m_tid;
}

bool ThreadBase::isAlive()
{
    return m_isAlive;
}

ThreadBase::~ThreadBase()
{
    // LOG(INFO) << "~ThreadBase tid=" << m_tid << endl;
    if (m_isAlive)
    {
        // LOG(INFO) << "Kill the thread tid= " << m_tid << endl;
        pthread_kill(m_tid, 0);
    }
}
