cmake_minimum_required(VERSION 3.1)

project(template)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

find_library(COCOA_LIBRARY Cocoa)

add_subdirectory(glfw)
add_subdirectory(glad)

set(SOURCES 
	src/app.cpp 
)

set(HEADERS
    include/shader.h
)

file(COPY ${PROJECT_SOURCE_DIR}/shaders DESTINATION ${RUNTIME_OUTPUT_DIRECTORY})

add_executable(app ${SOURCES} ${HEADERS})
target_link_libraries(app ${COCOA_LIBRARY} glfw glad)
