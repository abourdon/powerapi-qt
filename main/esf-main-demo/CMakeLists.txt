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
find_and_include(ESFCPUSensor)
find_and_include(ESFCPUFormula)
find_and_include(ESFNetworkSensor)
find_and_include(ESFNetworkFormula)
find_and_include(ESFMain)
find_and_include(Qt4)
set(PROJECT_CPP_MAIN_HEADERS_TO_MOC
    ${PROJECT_CPP_MAIN_SOURCE_DIR}/ThreadedLauncher.h
)
qt4_wrap_cpp(PROJECT_CPP_MAIN_HEADERS_MOCED ${PROJECT_CPP_MAIN_HEADERS_TO_MOC})

# Create the target executable
set(PROJECT_TARGET_EXECUTABLE ${PROJECT_NAME}-exe)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_EXECUTABLE_BINARY_DIR})
file(GLOB_RECURSE PROJECT_CPP_MAIN_SOURCES ${PROJECT_CPP_MAIN_SOURCE_DIR}/*.cpp)
add_executable(${PROJECT_TARGET_EXECUTABLE} ${PROJECT_CPP_MAIN_SOURCES} ${PROJECT_CPP_MAIN_HEADERS_MOCED})
target_link_libraries(${PROJECT_TARGET_EXECUTABLE} $ENV{ESF_LIBRARIES})

# Install process
install_process()

# Enable testing process
find_package(CxxTest)
if(CXXTEST_FOUND)        
    include_directories(${CXXTEST_INCLUDE_DIR})
    enable_testing()
    include(${CMAKE_SOURCE_DIR}/CMakeTestLists.txt)
endif()
