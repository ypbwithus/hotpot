#ifndef OpenGLTools_H
#define OpenGLTools_H

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <logHelper.h>
#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

using namespace std;

class OpenGLTools
{

public:
    static OpenGLTools *GetInstance();

    ~OpenGLTools();

private:
    OpenGLTools();

    // Not defined, to prevent copying
    OpenGLTools(const OpenGLTools &);
    OpenGLTools &operator=(const OpenGLTools &other);
};

// 一个静态函数去创建shader
unsigned int compileShader(unsigned int type, const std::string &source);
unsigned int creatShader(const std::string &vertexShader, const std::string &fragmentShader);

// struct ShaderProgramSource
// {
//     std::string vertexSource;
//     std::string fragmentSource;
// };

ShaderProgramSource parseShader(const std::string &filePath);

// void GLClearError();
// void GLCheckError();


#endif
