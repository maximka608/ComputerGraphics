cmake_minimum_required(VERSION 3.25)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

add_executable(OpenGL main.cpp)
target_link_libraries(OpenGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

