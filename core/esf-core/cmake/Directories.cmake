# --------------------------------------------------------------------
# Directories definition, according to the ESF Maven-like standard
# --------------------------------------------------------------------

# The project source directory
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

# Project source subdirectories
set(PROJECT_MAIN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/main)
set(PROJECT_TEST_SOURCE_DIR ${PROJECT_SOURCE_DIR}/test)

# Project main source subdirectories
set(PROJECT_CPP_MAIN_SOURCE_DIR ${PROJECT_MAIN_SOURCE_DIR}/cpp)
set(PROJECT_RESOURCES_MAIN_SOURCE_DIR ${PROJECT_MAIN_SOURCE_DIR}/resources)

# Project test source subdirectories
set(PROJECT_CPP_TEST_SOURCE_DIR ${PROJECT_TEST_SOURCE_DIR}/cpp)
set(PROJECT_RESOURCES_TEST_SOURCE_DIR ${PROJECT_TEST_SOURCE_DIR}/resources)

# The project target directory
set(PROJECT_BINARY_DIR ${CMAKE_BINARY_DIR})

# Project target subdirectories
set(PROJECT_LIBRARY_BINARY_DIR ${PROJECT_BINARY_DIR})
set(PROJECT_ARCHIVE_BINARY_DIR ${PROJECT_BINARY_DIR})
set(PROJECT_INCLUDE_BINARY_DIR ${PROJECT_BINARY_DIR}/include)
set(PROJECT_EXECUTABLE_BINARY_DIR ${PROJECT_BINARY_DIR})

# Project testing directory
set(PROJECT_TESTING_BINARY_DIR ${CMAKE_BINARY_DIR}/testing_launchers)
