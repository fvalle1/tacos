#python modules
if(UNIX)
    set( BOOST_PYTHONLIB python39)
else()
    set( BOOST_PYTHONLIB python3)
endif()

# Check the architecture and set CMAKE_LIBRARY_ARCHITECTURE accordingly
if(UNIX)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(CMAKE_LIBRARY_ARCHITECTURE "x86_64-linux-gnu")
    endif()
endif()

find_package(Boost 1.65.0 COMPONENTS ${BOOST_PYTHONLIB} timer REQUIRED)

find_package(PythonLibs 3.7 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "Boost_VERSION: ${Boost_VERSION}")
message(STATUS "Python_INCLUDE_DIRS: ${PYTHON_INCLUDE_DIRS}")
message(STATUS "Python_LIBRARIES: ${PYTHON__LIBRARY}")

include_directories(${CMAKE_SOURCE_DIR})

# Build our library
add_library(graphgenerator SHARED ${CMAKE_SOURCE_DIR}/GraphGenerator.cxx)

# Define the wrapper library that wraps our library
add_library(tacos SHARED
        GraphGenerator_Python.cxx
        ${CMAKE_SOURCE_DIR}/MainTable.cxx
        ${CMAKE_SOURCE_DIR}/SamplingModel.cxx
        ${CMAKE_SOURCE_DIR}/RandomGen.cxx
        ${CMAKE_SOURCE_DIR}/LabelsReshuffler.cxx)
# don't prepend wrapper library name with lib
set_target_properties(tacos PROPERTIES PREFIX "" )
# must be .so (not .dylib)
set_target_properties(tacos PROPERTIES SUFFIX ".so")

target_link_libraries(tacos ${PYTHON_LIBRARIES} ${Boost_LIBRARIES} graphgenerator curl)
