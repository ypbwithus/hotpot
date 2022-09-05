# cmake版本
cmake_minimum_required(VERSION 3.5.1)

# 项目名称
project(App)
message(--------${PROJECT_NAME}--------)

# ----------编译指令配置----------------------
# 采用C++11标准
set(CMAKE_CXX_STANDARD 17)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")

# ----------Qt 文件自动生成----------
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# ------------------安装目录------------------
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin/Release)
set(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin/Release)
set(CMAKE_INSTALL_PREFIX ${CMAKE_HOME_DIRECTORY}/bin/Release)

# ---------------------Qt ----------------------------
# 让cmake自动去寻找Qt5
list(APPEND CMAKE_PREFIX_PATH "D:/ProgramFiles/Qt/Qt5.12.2/5.12.2/msvc2017_64") # 安装路径前缀
FIND_PACKAGE(Qt5 COMPONENTS Widgets Core REQUIRED)

if(Qt5_FOUND)
	message("--------Qt5 Found-----------")
endif(Qt5_FOUND)

# ---------------------Qt ----------------------------
set(LIB_PATH ${CMAKE_HOME_DIRECTORY}/lib)

# ------------------CTK 框架------------------------
include_directories(
	${LIB_PATH}/libCTK/include/PluginFramework
	${LIB_PATH}/libCTK/include/Core
	${LIB_PATH}/libCTK/include/Widgets
)

link_libraries(
	${LIB_PATH}/libCTK/lib/CTKCore.lib
	${LIB_PATH}/libCTK/lib/CTKPluginFramework.lib
)

# ------------------CTK 框架------------------------

# ------------------glog------------------------

add_definitions(-DGOOGLE_GLOG_DLL_DECL)
add_definitions(-DGLOG_NO_ABBREVIATED_SEVERITIES)

include_directories(
	${LIB_PATH}/libglog/include/glog
	${LIB_PATH}/libglog/include
)

link_libraries(
	${LIB_PATH}/libglog/lib/glog.lib
)

# ------------------CTK 框架------------------------

# 添加所有的源文件
SET(App_SOURCES
	PluginPot/main.cpp
)

# 添加所有的头文件
SET(App_HEADERS
)

# 添加所有的.ui文件
SET(App_FORMS
)

# 添加资源文件
SET(App_RESOURCES
)

# 调用预编译器moc，需要使用 QT5_WRAP_CPP宏
QT5_WRAP_CPP(App_HEADERS_MOC ${App_HEADERS})

# 使用uic处理.ui文件
QT5_WRAP_UI(App_FORMS_HEADERS ${App_FORMS})

# 使用rcc处理.qrc文件
QT5_ADD_RESOURCES(App_RESOURCES_RCC ${App_RESOURCES})

# 这些生成的中间文件都会在build目录下，这样的话，编译器则不能定位由uic程序产生的诸如_ui_mainwindow.h等文件。所以，我们需要把build目录添加到包含目录中
include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CMAKE_HOME_DIRECTORY}/include)

add_subdirectory(${CMAKE_HOME_DIRECTORY}/spices/log)
include_directories(${CMAKE_HOME_DIRECTORY}/spices/log)

# add_subdirectory(${CMAKE_HOME_DIRECTORY}/PluginsVegetables/HelloCTK)
# add_subdirectory(${CMAKE_HOME_DIRECTORY}/PluginsVegetables/Plate)

add_subdirectory(${CMAKE_HOME_DIRECTORY}/PluginsVegetables/PlateOpenGL)
include_directories(${CMAKE_HOME_DIRECTORY}/PluginsVegetables/PlateOpenGL)

add_subdirectory(${CMAKE_HOME_DIRECTORY}/PluginsVegetables/SharedLibImport)
include_directories(${CMAKE_HOME_DIRECTORY}/PluginsVegetables/SharedLibImport)

# 生成可执行文件
add_executable(
	${PROJECT_NAME}
	${App_SOURCES}
	${App_HEADERS_MOC}
	${App_FORMS_HEADERS}
	${App_RESOURCES_RCC}
)

target_link_libraries(
	${PROJECT_NAME}
	${Qt5Widgets_LIBRARIES}
	logHelper
	SharedLibImport
)
