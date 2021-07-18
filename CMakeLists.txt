include(ExternalProject)
cmake_minimum_required (VERSION 3.4)
project(cicada)

set(CXX_FLAGS
    -g
    -O0
)

set(CMAKE_CXX_STANDARD 17)

include("CMakeLists.txt.in")

include_directories(${PROJECT_SOURCE_DIR})

enable_testing()

add_subdirectory(cicada)
add_subdirectory(examples)


#install(TARGETS cicada
#    LIBRARY DESTINATION lib  # 动态库安装路径
#    ARCHIVE DESTINATION lib  # 静态库安装路径
#    RUNTIME DESTINATION bin  # 可执行文件安装路径
#    PUBLIC_HEADER DESTINATION include  # 头文件安装路径
#)
