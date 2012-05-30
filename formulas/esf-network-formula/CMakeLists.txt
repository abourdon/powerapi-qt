# --------------------------------------------------------------------
# ESF bundle project definition
# --------------------------------------------------------------------

# CMake minimum version required
cmake_minimum_required(VERSION 2.8.3)

# Project definitions and configurations
project(${ESF_BUNDLE_NAME})
set(ENV{ESF_LIBRARIES} "")

include(${CMAKE_SOURCE_DIR}/cmake/Directories.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/Util.cmake)

# Find and include needed libraries
find_and_include(SOF)
find_and_include(ESFCore)
find_and_include(ESFNetworkSensor)
find_and_include(Qt4)
set(PROJECT_CPP_MAIN_HEADERS_TO_MOC
    ${PROJECT_CPP_MAIN_SOURCE_DIR}/business/NetworkFormulaComputer.h
)
qt4_wrap_cpp(PROJECT_CPP_MAIN_HEADERS_MOCED ${PROJECT_CPP_MAIN_HEADERS_TO_MOC})

# Create the target library
set(PROJECT_TARGET_LIBRARY ${PROJECT_NAME})
file(GLOB_RECURSE PROJECT_CPP_MAIN_SOURCES ${PROJECT_CPP_MAIN_SOURCE_DIR}/*.cpp)
add_library(${PROJECT_TARGET_LIBRARY} ${PROJECT_CPP_MAIN_SOURCES} ${PROJECT_CPP_MAIN_HEADERS_MOCED})
target_link_libraries(${PROJECT_TARGET_LIBRARY} $ENV{ESF_LIBRARIES})

# Install process
install_process()

# Enable testing process
find_package(CxxTest)
if(CXXTEST_FOUND)        
    include_directories(${CXXTEST_INCLUDE_DIR})
    enable_testing()
    include(${CMAKE_SOURCE_DIR}/CMakeTestLists.txt)
endif()
