cmake_minimum_required (VERSION 3.4)
project(cicada)

set(CXX_FLAGS
    -std=c++17
)

add_subdirectory(examples)

#install(TARGETS cicada
#    LIBRARY DESTINATION lib  # 动态库安装路径
#    ARCHIVE DESTINATION lib  # 静态库安装路径
#    RUNTIME DESTINATION bin  # 可执行文件安装路径
#    PUBLIC_HEADER DESTINATION include  # 头文件安装路径
#)
