#include <VertexArray.h>

#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RendererID));
    // GLCall(glBindVertexArray(m_RendererID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    Bind();
    vb.Bind();
    const auto &elements = layout.GetElments();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto &element = elements[i];

        LOG(INFO) << i
                  << ":" << element.count
                  << ":" << element.type
                  << ":" << element.normalized
                  << ":" << layout.GetStride();
                  
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type,
                                     element.normalized, layout.GetStride(), (const void *)offset));

        offset += element.count * VertexBufferLayoutElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}