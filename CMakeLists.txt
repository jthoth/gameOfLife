cmake_minimum_required(VERSION 3.15)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 14)

set(OpenGlLinkers -lglut -lGLU -lGL)
set(OpenClLinkers -lOpenCL)


add_executable(GameOfLife main.cpp
                view/Windows.cpp view/Windows.h
                serial/ConwayGame.cpp serial/ConwayGame.h
                opencl/OpenClProgram.cpp opencl/OpenClProgram.h opencl/ConwayGameCl.cpp opencl/ConwayGameCl.h)

target_link_libraries(GameOfLife ${OpenGlLinkers})
target_link_libraries(GameOfLife ${OpenClLinkers})