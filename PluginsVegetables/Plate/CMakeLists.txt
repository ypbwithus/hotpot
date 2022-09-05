#cmake版本
cmake_minimum_required(VERSION 3.5.1)

#项目名称
project(Plate)
message(--------${PROJECT_NAME}--------)

#让cmake自动去寻找Qt5
FIND_PACKAGE(Qt5 COMPONENTS Widgets Core REQUIRED)
# if(Qt5_FOUND)
# 	message("--------Qt5 Found-----------")
# endif(Qt5_FOUND)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#采用C++11标准
set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin/Release/PluginsVegetables/Plate)
set(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin/Release/PluginsVegetables/Plate)
set(CMAKE_INSTALL_PREFIX ${CMAKE_HOME_DIRECTORY}/bin/Release/PluginsVegetables/Plate)

set(LIB_PATH ${CMAKE_HOME_DIRECTORY}/lib)

include_directories(
	${LIB_PATH}/libCTK/include/PluginFramework
	${LIB_PATH}/libCTK/include/Core
	${LIB_PATH}/libCTK/include/Widgets
)

link_libraries(
	${LIB_PATH}/libCTK/lib/CTKCore.lib
	${LIB_PATH}/libCTK/lib/CTKPluginFramework.lib
)

#添加所有的源文件
SET(App_SOURCES 
	PlateActivator.cpp
	PlateImpl.cpp
)

#添加所有的头文件
SET(App_HEADERS 
	PlateActivator.h
	PlateImpl.h
	PlateService.h
)

#添加所有的.ui文件
SET(App_FORMS 
)

#添加资源文件
SET(App_RESOURCES 
	Plate.qrc
)

#调用预编译器moc，需要使用 QT5_WRAP_CPP宏
QT5_WRAP_CPP(App_HEADERS_MOC ${App_HEADERS})
#使用uic处理.ui文件
QT5_WRAP_UI(App_FORMS_HEADERS ${App_FORMS})
#使用rcc处理.qrc文件
QT5_ADD_RESOURCES(App_RESOURCES_RCC ${App_RESOURCES})

#这些生成的中间文件都会在build目录下，这样的话，编译器则不能定位由uic程序产生的诸如_ui_mainwindow.h等文件。所以，我们需要把build目录添加到包含目录中
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#生成可执行文件
add_library(
	${PROJECT_NAME} SHARED
	${App_SOURCES} 
	${App_HEADERS_MOC} 
    ${App_FORMS_HEADERS}
	${App_RESOURCES_RCC} 
)

target_link_libraries(
	${PROJECT_NAME} 
	${Qt5Widgets_LIBRARIES}
)
