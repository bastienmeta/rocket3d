cmake_minimum_required(VERSION 3.1)

project(RocketGame)

set(CMAKE_CXX_STANDARD 11)
if(CMAKE_GENERATOR STREQUAL Xcode)
    set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
else()
    set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/Debug)
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/Debug)
endif()

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.h)
file(GLOB SHADERS shaders/*.glsl)

find_library(COCOA_LIBRARY Cocoa)
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

add_subdirectory(glfw)
add_subdirectory(glad)
add_executable(app ${SOURCES} ${HEADERS} ${SHADERS})
target_link_libraries(app ${COCOA_LIBRARY} glfw glad)
