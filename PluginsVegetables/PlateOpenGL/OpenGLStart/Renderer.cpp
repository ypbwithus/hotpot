#include <Renderer.h>

#include "Shader.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

// void GLCheckError()
// {
//     while (GLenum error = glGetError())
//     {
//         LOG(FATAL) << "[OepnGL Error](" << error << ")";
//     }
// }

std::tuple<int, unsigned int> GLCheckError()
{
    while (GLenum error = glGetError())
    {
        // LOG(FATAL) << "[OepnGL Error](" << error << ")";
        return std::make_pair(-1, error);
    }

    return std::make_tuple<int, unsigned int>(0, 0);
}

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

 void Renderer::SetClearColor() const
 {

 }