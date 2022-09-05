#pragma once

#include <functional>
#include <vector>
#include <string>

#include <logHelper.h>

namespace test
{
    class Test
    {
    public:
        Test() {}
        virtual ~Test() {}

        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}
    };

    class TestMenue : public Test
    {
    public:
        TestMenue(Test *&currentTestPointer);
        virtual ~TestMenue();

        void OnImGuiRender() override;

        template <typename T>
        void RegisterTest(const std::string &name)
        {
            LOG(INFO) << "Registering Test " << name;

            // 新创建T对象
            m_Tests.push_back(std::make_pair(name,
                                             []()
                                             { return new T(); }));
        }

    private:
        Test *&m_CurrentTest;

        std::vector<std::pair<std::string, std::function<Test *()>>> m_Tests;
    };
}
