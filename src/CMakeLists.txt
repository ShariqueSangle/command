
cmake_minimum_required(VERSION 3.5)

set(CMAKE_MAKE_PROGRAM "D:/make/GnuWin32/bin/make.exe" CACHE INTERNAL "" FORCE)

set(CMAKE_C_COMPILER "D:/Perl/c/bin/gcc.exe")

set(CMAKE_CXX_COMPILER "D:/Perl/c/bin/g++.exe")

project(command)

include_directories(include)

add_executable(binary main.cpp functions.cpp)

add_library(glfw3 STATIC IMPORTED)

set_target_properties(glfw3 PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libglfw3.a)

target_link_libraries(binary PRIVATE
    opengl32
    gdi32
    glfw3
)
