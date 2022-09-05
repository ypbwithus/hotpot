#ifndef OpenGLStart_H
#define OpenGLStart_H

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <logHelper.h>


// #include <gl/GL.h>
// #include <gl/GLU.h>


using namespace std;

class OpenGLStart
{

public:
    static OpenGLStart *GetInstance();

    ~OpenGLStart();

private:
    OpenGLStart();

    // Not defined, to prevent copying
    OpenGLStart(const OpenGLStart &);
    OpenGLStart &operator=(const OpenGLStart &other);

public:
    // 0,测试环境画一个三角形
    void testOpenGLEnv();

    // 2,着色器，shader
    // 渲染管线

    void imguiOpenGLEnv();
};

#endif
