cmake_minimum_required(VERSION 3.25)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS system thread)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(untitled main.cpp)

target_link_libraries(untitled PRIVATE ${Boost_LIBRARIES})