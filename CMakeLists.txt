cmake_minimum_required(VERSION 3.14)
project(OpenGL-cpp VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}>) # To have the executable file at the root of the build directory
set(PROJECT_LIB ${PROJECT_NAME}-lib)
set(PROJECT_EXEC ${PROJECT_NAME})

find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(
    deps/glad/include
    deps/stb/include
    deps/glm/include
    src/
)

set(SOURCES
    deps/glad/src/glad.c
    src/Shader.cpp
    src/Utils.cpp
    src/Texture.cpp
    src/Camera.cpp
)

add_library(${PROJECT_LIB} ${SOURCES})

add_executable(${PROJECT_EXEC} Main.cpp)
target_link_libraries(${PROJECT_EXEC}
    PRIVATE OpenGL::GL
    PRIVATE glfw
    PRIVATE ${PROJECT_LIB}
)

set(RES_FOLDER_SRC ${CMAKE_CURRENT_SOURCE_DIR}/res)
set(RES_FOLDER_DST ${CMAKE_BINARY_DIR}/res)

add_custom_target(copy_res ALL COMMAND ${CMAKE_COMMAND} -E copy_directory ${RES_FOLDER_SRC} ${RES_FOLDER_DST})