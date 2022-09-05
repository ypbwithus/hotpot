#include "TestTexture2D.h"

#include "Renderer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace test
{

    TestTexture2D::TestTexture2D()
        : m_translationA(200, 200, 0), m_translationB(400, 100, 0),
          m_translationA_Scale(1, 1, 1), m_translationB_Scale(2, 2, 0)
    {
        float positions[] =
            {
                -50.0f, -50.0f, 0.0f, 0.0f, // 0
                50.0f, -50.0f, 1.0f, 0.0f,  // 1
                50.0f, 50.0f, 1.0f, 1.0f,   // 2
                -50.0f, 50.0f, 0.0f, 1.0f   // 3
            };

        unsigned int indices[] =
            {
                0, 1, 2, // 第1个三角形
                2, 3, 0  // 第2个三角形
            };

        m_Proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f); // 投影
        m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)); // 平移
        m_Scale = glm::scale(glm::mat4(1.0f), glm::vec3(5, 5, 5));    // 缩放

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_VAO = std::make_unique<VertexArray>();

        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VertexBuffer, layout);

        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);
        m_IndexBuffer->Bind();

        m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", 1.0, 0.3, 0.8, 0.1);

        m_Texture = std::make_unique<Texture>("res/textures/zhoulun.jpg");

        m_Texture->Bind();
        m_Shader->SetUniform1i("u_Texture", 0);

        // m_VAO->Unbind();
        // vb.Unbind();
        // ib.Unbind();
        // shader.Unbind();
    }

    TestTexture2D::~TestTexture2D()
    {
    }

    void TestTexture2D::OnUpdate(float deltaTime)
    {
    }

    void TestTexture2D::OnRender()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        m_Texture->Bind(0);

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
            m_Scale = glm::scale(glm::mat4(1.0f), m_translationA_Scale); // 缩放
            glm::mat4 mvp = m_Proj * m_View * model * m_Scale;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationB);
            m_Scale = glm::scale(glm::mat4(1.0f), m_translationB_Scale);
            glm::mat4 mvp = m_Proj * m_View * model * m_Scale;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
    }

    void TestTexture2D::OnImGuiRender()
    {
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::SliderFloat3("Translation A", &m_translationA.x, 0.0f, 960.0f);
            ImGui::SliderFloat3("Translation A Scale", &m_translationA_Scale.x, 0.0f, 10.0f);
            ImGui::SliderFloat3("Translation B", &m_translationB.x, 0.0f, 960.0f);
            ImGui::SliderFloat3("Translation B Scale", &m_translationB_Scale.x, 0.0f, 10.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
    }

}
