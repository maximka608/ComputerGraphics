cmake_minimum_required(VERSION 3.25)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

add_executable(OpenGL lab1.cpp lab2.cpp include/stb_image.h lab3.cpp include/json.hpp)
target_link_libraries(OpenGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

