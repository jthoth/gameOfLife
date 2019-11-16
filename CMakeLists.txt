cmake_minimum_required(VERSION 3.15)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 14)
set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.


add_executable(GameOfLife main.cpp view/Windows.cpp view/Windows.h serial/ConwayGame.cpp serial/ConwayGame.h)
target_link_libraries(GameOfLife ${OpenGlLinkers}) # linking opengl libraries to the project
