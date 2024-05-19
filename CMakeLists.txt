cmake_minimum_required(VERSION 3.22)
project(DA_RoutingAlgorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(DA_RoutingAlgorithms
        src/models/Graph.h
        src/utils/DataStructures/Heap.cpp
        src/utils/DataStructures/Heap.h
        src/utils/DataStructures/MutablePriorityQueue.h
        src/utils/DataStructures/UFDS.cpp
        src/utils/DataStructures/UFDS.h
        src/utils/Dataset.cpp
        src/utils/Dataset.h
        src/main.cpp
        src/models/Graph.cpp
        src/models/VertexEdge.cpp
        src/views/Menu.h
        src/views/Menu.cpp
        src/models/TSPSimulatedAnnealing.cpp
        src/models/TSPSimulatedAnnealing.h)


# Doxygen Build
find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if (NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif ()

    set(DOXYGEN_IN "docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else (DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif (DOXYGEN_FOUND)
