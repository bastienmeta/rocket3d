cmake_minimum_required(VERSION 3.1)

project(template)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

find_library(COCOA_LIBRARY Cocoa)

add_subdirectory(glfw)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES 
	src/app.cpp 
	src/glad.c
)

add_executable(app ${SOURCES})

target_include_directories(app PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/glad
	${CMAKE_CURRENT_SOURCE_DIR}/glfw/include
)
target_link_libraries(app glfw ${COCOA_LIBRARY})
