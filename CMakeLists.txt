cmake_minimum_required (VERSION 2.6)
project (EntitySystem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE TEST_SOURCES src_test/*.cpp)

add_subdirectory(thirdparty/gmock-1.7.0)
include_directories(src)
include_directories(thirdparty/gmock-1.7.0/include)
include_directories(thirdparty/gmock-1.7.0/gtest/include)

add_executable(EntitySystemTests ${SOURCES} ${TEST_SOURCES})
target_link_libraries(EntitySystemTests gmock_main)

enable_testing()
add_test(AllTests EntitySystemTests)