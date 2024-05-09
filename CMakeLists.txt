cmake_minimum_required(VERSION 3.28)
project(DA_RoutingAlgorithms)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/utils)
include_directories(src/utils/DataStructures)

add_executable(DA_RoutingAlgorithms
        src/utils/DataStructures/Graph.h
        src/utils/DataStructures/Heap.cpp
        src/utils/DataStructures/Heap.h
        src/utils/DataStructures/MutablePriorityQueue.h
        src/utils/DataStructures/UFDS.cpp
        src/utils/DataStructures/UFDS.h
        src/utils/Dataset.cpp
        src/utils/Dataset.h
        src/main.cpp)
