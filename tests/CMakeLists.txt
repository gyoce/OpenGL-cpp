cmake_minimum_required(VERSION 3.14)

include_directories(
    deps/glad/include
    deps/stb/include
    src/
)

set(PROJECT_EXEC_TEST ${PROJECT_NAME}TEsts)

find_package(GTest CONFIG REQUIRED)
add_executable(${PROJECT_EXEC_TEST}
    TestsVec3.cpp
    TestsVec4.cpp 
    TestsMat4.cpp
)
target_link_libraries(${PROJECT_EXEC_TEST} ${PROJECT_LIB} GTest::gtest_main GTest::gtest)
include(GoogleTest)

gtest_discover_tests(${PROJECT_EXEC_TEST})