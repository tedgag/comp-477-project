cmake_minimum_required(VERSION 3.17)
project(comp477project)

set(CMAKE_CXX_STANDARD 14)
# Add source files
file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        )

# Add header files
file(GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/src/*.hpp
        ${CMAKE_SOURCE_DIR}/lib/stb/stb_image.h
        )
# Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} src/InstancedRenderer.cpp src/InstancedRenderer.h)
# Configure assets header file
configure_file(src/helpers/RootDir.h.in src/helpers/RootDir.h)
include_directories(${CMAKE_BINARY_DIR}/src)
# glfw
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(comp477project PRIVATE glfw)

# glew
add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
target_link_libraries(comp477project PRIVATE libglew_static)

# glm
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(comp477project PRIVATE glm)
# assimp
add_subdirectory(lib/assimp EXCLUDE_FROM_ALL)
target_link_libraries(comp477project PRIVATE assimp)
# stb
include_directories(lib/stb)
