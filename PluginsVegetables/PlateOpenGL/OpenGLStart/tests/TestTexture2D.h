#pragma once

#include "Test.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

namespace test
{
    class TestTexture2D : public Test
    {
    public:
        TestTexture2D();
        virtual ~TestTexture2D();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;

        glm::vec3 m_translationA;
        glm::vec3 m_translationA_Scale;
        glm::vec3 m_translationB;
         glm::vec3 m_translationB_Scale;

        glm::mat4 m_Proj;
        glm::mat4 m_View;
        glm::mat4 m_Scale;
    };
}
