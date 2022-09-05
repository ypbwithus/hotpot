# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)
aux_source_directory(./imgui DIR_LIB_SRCS)
aux_source_directory(./tests DIR_LIB_SRCS)

include_directories(. )
include_directories(./glm)
include_directories(./imgui)
include_directories(./tests)

# 生成链接库
add_library (OpenGLStart ${DIR_LIB_SRCS})