cmake_minimum_required(VERSION 3.13)
project(tacos_main)

# Set modern CMake policies to suppress warnings
cmake_policy(SET CMP0144 NEW)  # Use <PackageName>_ROOT variables
cmake_policy(SET CMP0167 NEW)  # Use BoostConfig.cmake



set(CMAKE_CXX_STANDARD 14)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
message(STATUS "Python3_VERSION: ${Python3_VERSION}")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(BOOST_ROOT ~/boost)
set(Boost_PYTHON_VERSION ${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR})

find_package(Boost REQUIRED COMPONENTS python)

find_package(Boost 1.83.0 COMPONENTS system timer random REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(
            ~/anaconda3/include
            pcg
    )

    add_executable(
            tacos_tool
            main.cpp
            MainTable.cxx
            SamplingModel.cxx
            RandomGen.cxx
            GraphGenerator.cxx
            BioParameters.cxx
            LabelsReshuffler.cxx)

    target_link_libraries(tacos_tool ${Boost_LIBRARIES})
    target_link_libraries(tacos_tool curl)
endif()

add_subdirectory(python)
