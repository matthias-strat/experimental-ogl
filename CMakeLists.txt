cmake_minimum_required(VERSION 2.6)

project(cube3d)

set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")

include_directories(mgl/include)

set(SRC_LIST mgl/include/mgl/GLSLProgram.hpp
			 mgl/source/GLSLProgram.cpp 
			 Main.cpp)

add_executable(cube3d ${SRC_LIST})
target_link_libraries(cube3d GLEW GL sfml-graphics sfml-window sfml-system)