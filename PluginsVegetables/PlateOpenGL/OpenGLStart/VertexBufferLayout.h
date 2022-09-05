#pragma once

#include <GL/glew.h>
#include <logHelper.h>
#include <vector>

struct VertexBufferLayoutElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT:
            return 4;

        case GL_UNSIGNED_INT:
            return 4;

        case GL_UNSIGNED_BYTE:
            return 1;

        default:
            return 0;
        }
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferLayoutElement> m_Element;
    unsigned int m_Stride;

public:
    VertexBufferLayout()
        : m_Stride(0) {}

    ~VertexBufferLayout(){};

public:
    template <typename T>
    void Push(unsigned int count)
    {
        static_assert(false);
    }

    template <>
    void Push<float>(unsigned int count)
    {
        m_Element.push_back({GL_FLOAT, count, GL_FALSE});
        // m_Stride += sizeof(GLfloat);
        m_Stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_FLOAT);
    }

    template <>
    void Push<unsigned int>(unsigned int count)
    {
        m_Element.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        // m_Stride += sizeof(GLuint);
        m_Stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    template <>
    void Push<unsigned char>(unsigned int count)
    {
        m_Element.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        // m_Stride += sizeof(GLbyte);
        m_Stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<VertexBufferLayoutElement> GetElments() const { return m_Element; };
    inline unsigned int GetStride() const { return m_Stride; };
};