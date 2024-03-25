cmake_minimum_required(VERSION 3.27)
project(ProjetoDA)

set(CMAKE_CXX_STANDARD 17)

add_executable(ProjetoDA src/main.cpp
        src/Menu.h
        src/Menu.cpp
        src/System.h
        src/System.cpp
        src/Graph.h
        src/Graph.cpp
        src/Node.h
        src/Node.cpp
        src/Pipeline.h
        src/Pipeline.cpp)

