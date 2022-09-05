#include "blog_manager.h"
#include "blog_manager_activator.h"
#include <QtDebug>
#include <thread>

void BlogManagerActivator::start(ctkPluginContext *context)
{
    m_pBlogManager = new BlogManager(context);

    Blog blog;
    blog.title = "CTK Event Admin";
    blog.content = "This is a simple blog";
    blog.author = "Waleon";
    m_pBlogManager->publishBlog(blog);

//    std::thread *t = new std::thread([this](){
//        for(int i = 0 ;i < 100;i++)
//        {
//            qDebug() << "testPublish";
//            std::this_thread::sleep_for(std::chrono::milliseconds(1));

//            this->testPublish();
//        }
//    });

//    t->detach();
}

void BlogManagerActivator::stop(ctkPluginContext *context)
{
    Q_UNUSED(context)

    delete m_pBlogManager;
}

void BlogManagerActivator::testPublish()
{
    Blog blog;
    blog.title = "CTK Event Admin";
    blog.content = "This is a simple blog";
    blog.author = "Waleon";

    this->m_pBlogManager->publishBlog(blog);
}
