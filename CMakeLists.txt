
#/**
#* Name: Vishal Subramanyam
#* Roll Number: 20CS10081
#* Email addr: vishalsubramanyam02@gmail.com
#*/
cmake_minimum_required(VERSION 3.25)
project(assignment2 LANGUAGES CXX)
execute_process(
        COMMAND git pull
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
add_executable(main src/main.cpp
        src/generate_landscape.cpp
        src/lighting.cpp
        src/input_handlers.cpp)
target_link_libraries(main PRIVATE GLUT::GLUT OpenGL::OpenGL OpenGL::GLU)
target_include_directories(main PRIVATE include)