cmake_minimum_required(VERSION 3.20)
project(Proj_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(Tests)

add_executable(Proj_2
        Tests/stcp.cpp
        Tests/line.cpp
        Tests/stop.cpp
        Tests/graph.cpp
        main.cpp)
