# $ cmake --version
cmake_minimum_required(VERSION 3.16)

# Project Name
project(RoboticArm)

# Find the required packages
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Include the directories for OpenGL and GLUT
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

# Set the output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

# Source files
add_executable(
    Navigator
    Navigator.cpp
    glm.c
)

# Link the executable with the required libraries
target_link_libraries(Navigator ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})