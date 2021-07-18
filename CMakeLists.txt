include(ExternalProject)
cmake_minimum_required (VERSION 3.4)
project(cicada)

set(CXX_FLAGS
    -std=c++17
    -Wc++17-extensions
)

#find_package(Protobuf)
#configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

#execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
#    RESULT_VARIABLE result
#    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
#if(result)
#    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
#endif()
#execute_process(COMMAND ${CMAKE_COMMAND} --build .
#    RESULT_VARIABLE result
#    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
#if(result)
#    message(FATAL_ERROR "Build step for googletest failed: ${result}")
#endif()

ExternalProject_Add(
    google_gtest
    URL https://github.com/google/googletest/archive/release-1.8.0.zip
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/gtest
    SOURCE_DIR ${CMAKE_BINARY_DIR}/thirdparty/gtest/source
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/thirdparty/gtest/build -DBUILD_SHARED_LIBS=OFF
)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR}/thirdparty/gtest/build/include)

link_directories(${CMAKE_BINARY_DIR}/thirdparty/gtest/build/lib)

enable_testing()

add_subdirectory(cicada)
add_subdirectory(examples)


#install(TARGETS cicada
#    LIBRARY DESTINATION lib  # 动态库安装路径
#    ARCHIVE DESTINATION lib  # 静态库安装路径
#    RUNTIME DESTINATION bin  # 可执行文件安装路径
#    PUBLIC_HEADER DESTINATION include  # 头文件安装路径
#)
