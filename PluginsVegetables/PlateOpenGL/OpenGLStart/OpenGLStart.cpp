#include "OpenGLStart.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

#include "VertexArray.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "TestClearColor.h"
#include "TestTexture2D.h"

using namespace test;

OpenGLStart *OpenGLStart::GetInstance()
{
    LOG(INFO) << "Get Instance of OpenGLStart";

    // Initialized during first access
    static OpenGLStart inst;

    return &inst;
}

OpenGLStart::OpenGLStart()
{

    LOG(INFO) << "Instance OpenGLStart";

    testOpenGLEnv();
    // imguiOpenGLEnv();
}

OpenGLStart::~OpenGLStart()
{
    // LOG(INFO) << "In Destructor of OpenGLStart" << endl;
}
void OpenGLStart::imguiOpenGLEnv()
{
    thread *t = new thread(

        []() {

        }

    );
}

void OpenGLStart::testOpenGLEnv()
{
    thread *t = new thread(

        []()
        {
            GLFWwindow *window;

            /* Initialize the library */
            if (!glfwInit())
                return -1;

            /* Create a windowed mode window and its OpenGL context */
            window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
            if (!window)
            {
                glfwTerminate();
                return -1;
            }

            /* Make the window's context current */
            glfwMakeContextCurrent(window);

            glfwSwapInterval(1);

            if (glewInit() != GLEW_OK)
            {
                LOG(INFO) << "glewInit is not OK";
            }

            // OpenGL输出版本
            LOG(INFO) << glGetString(GL_VERSION);

            Renderer rederer;

            // -------------imgui------------------
            const char *glsl_version = "#version 330";
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO &io = ImGui::GetIO();
            (void)io;

            // Setup Dear ImGui style
            ImGui::StyleColorsDark();
            // ImGui::StyleColorsClassic();

            // Setup Platform/Renderer backends
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init(glsl_version);
            // -------------imgui------------------

            test::Test *currentTest;
            test::TestMenue *testMenu = new test::TestMenue(currentTest);
            currentTest = testMenu;

            testMenu->RegisterTest<test::TestClearColor>("clear Color");
            testMenu->RegisterTest<test::TestTexture2D>("TestTexture2D");

            /* Loop until the user closes the window */
            while (!glfwWindowShouldClose(window))
            {
                GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
                rederer.Clear();

                // -------------imgui------------------
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();
                // -------------imgui------------------

                // test.OnImGuiRender();
                if (currentTest)
                {
                    currentTest->OnUpdate(0.0f);
                    currentTest->OnRender();
                    ImGui::Begin("Test");
                    if (currentTest != testMenu && ImGui::Button("<-"))
                    {
                        delete currentTest;
                        currentTest = testMenu;
                    }

                    currentTest->OnImGuiRender();

                    ImGui::End();
                }

                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                glfwSwapBuffers(window);
                glfwPollEvents();
            }

            delete currentTest;
            if (currentTest != testMenu)
            {
                delete testMenu;
            }

            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
            glfwTerminate();
            return 0;
        });

    t->detach();
}
