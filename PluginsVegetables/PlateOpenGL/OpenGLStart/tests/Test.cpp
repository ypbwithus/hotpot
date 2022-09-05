#include "Test.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace test
{
    TestMenue::TestMenue(Test *& currentTestPointer)
    : m_CurrentTest(currentTestPointer)
    {
    }

    TestMenue::~TestMenue()
    {
    }
 
    void TestMenue::OnImGuiRender()
    {
        for (auto & test : m_Tests)
        {
            if(ImGui::Button(test.first.c_str()))
            {
                m_CurrentTest = test.second();
            }
        }
        
    }
}
