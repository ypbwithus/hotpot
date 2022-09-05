#pragma once

#include <GL/glew.h>
#include <logHelper.h>
#include <tuple>
#include "VertexArray.h"
#include "IndexBuffer.h"

void GLClearError();
// void GLCheckError();
std::tuple<int, unsigned int> GLCheckError();

#define GLCall(x)                                                       \
    GLClearError();                                                     \
    x;                                                                  \
    {                                                                   \
        std::tuple<int, unsigned int> res = GLCheckError();             \
        if (std::get<0>(res) == -1)                                     \
        {                                                               \
            LOG(FATAL) << "[OepnGL Error](" << std::get<1>(res) << ")"; \
        }                                                               \
    }

class Shader;

class Renderer
{
public:
    void Clear() const;
    void SetClearColor() const;
    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
};
