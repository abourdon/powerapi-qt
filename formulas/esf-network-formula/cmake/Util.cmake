# --------------------------------------------------------------------
# Useful stuffs
# --------------------------------------------------------------------

# We don't want to have to bother having IF() ELSE() and ENDIF() conditions match
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)

# We always want to deal with shared libraries
set(BUILD_SHARED_LIBS ON)

# Overrides the CMAKE_MODULE_PATH search path in order to point to our ${CMAKE_SOURCE_DIR}/cmake/Modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)

# Find and include the package given in argument
#
# @param PACKAGE_NAME, the package name to find, include and link
# @return void
# @throw an error if the package is not found
function(find_and_include PACKAGE_NAME)
    # This implementation only does a switch in order to choose
    # the right _find_and_include.* method to call
    
    # SOF case
    if(${PACKAGE_NAME} STREQUAL "SOF")
        _find_and_include_sof()
    # Qt4 case
    elseif(${PACKAGE_NAME} STREQUAL "Qt4")
        _find_and_include_qt4()
    # Default case
    else()
        _find_and_include_default(${PACKAGE_NAME})
    endif()
endfunction(find_and_include)

# SOF specific find_and_include
#
# @see find_and_include for more details
function(_find_and_include_sof)
    _find_and_include_default(SOF)
    link_directories(${CMAKE_THREAD_LIBS} ${CMAKE_DL_LIBS})
endfunction(_find_and_include_sof)

# Qt4 specific find_and_include
#
# @see find_and_include for more details
function(_find_and_include_qt4)
    find_package(Qt4 COMPONENTS QtCore QtSQL REQUIRED)
    include(${QT_USE_FILE})
    add_definitions(${QT_DEFINITIONS})
    add_libraries(${QT_LIBRARIES})
endfunction(_find_and_include_qt4)

# Default find_and_include
#
# @see find_and_include for more details
function(_find_and_include_default PACKAGE_NAME)
    find_package(${PACKAGE_NAME} REQUIRED)
    include_directories(${${PACKAGE_NAME}_INCLUDE_DIRS})
    link_directories(${${PACKAGE_NAME}_LIBRARY_DIRS})
    add_libraries(${${PACKAGE_NAME}_LIBRARIES})
endfunction(_find_and_include_default)

# Add the library list given in argument to the global library list
# represented by the ENV{ESF_LIBRARIES} environment variable
#
# @return void
function(add_libraries)
    set(ENV{ESF_LIBRARIES} "$ENV{ESF_LIBRARIES};${ARGV}")
endfunction(add_libraries)

# Do some initial configurations for the test process
#
# @return void
function(init_tests)
    # Create the project testing binary directory
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${PROJECT_TESTING_BINARY_DIR}
    )

    # Copy resources directories (main and test) to the binary one
    #
    # Main resources are proceeded first, to let overriding
    # by test one
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_RESOURCES_MAIN_SOURCE_DIR}
        ${PROJECT_TESTING_BINARY_DIR}
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_RESOURCES_TEST_SOURCE_DIR}
        ${PROJECT_TESTING_BINARY_DIR}
    )
    
    # Configure the TestUtil class with specific plateform options
    configure_file(
        ${PROJECT_CPP_TEST_SOURCE_DIR}/util/TestUtil.h.in
        ${PROJECT_CPP_TEST_SOURCE_DIR}/util/TestUtil.h
    )
endfunction(init_tests)

# Add a test according to the test source directory
# and test name given
#
# We assume that all tests correspond to the folowing
# nomenclature:
# - header file: ${TEST_SOURCE_DIR}/${TEST_NAME}.h
# - source file: ${TEST_SOURCE_DIR}/${TEST_NAME}.cpp
#
# Warning, this function RUN EXCLUSIVELY with CxxTest
#
# @param TEST_SOURCE_DIR, the directory where the test
#   come from
# @param TEST_NAME, the test name
# @return void
function(custom_add_test TEST_SOURCE_DIR TEST_NAME)
    set(CMAKE_CURRENT_BINARY_DIR ${PROJECT_TESTING_BINARY_DIR})
	cxxtest_add_test(
		${TEST_NAME}
		${TEST_NAME}.cxx
		${TEST_SOURCE_DIR}/${TEST_NAME}.h
		${TEST_SOURCE_DIR}/${TEST_NAME}.cpp
	)
	target_link_libraries(${TEST_NAME} ${PROJECT_TARGET_LIBRARY})
	set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_TESTING_BINARY_DIR})
endfunction(custom_add_test)


# Install project process
#
# Install:
#    - headers
#    - resources
#
# @return void
function(install_process)
    # Project headers installation
    install(
        DIRECTORY ${PROJECT_CPP_MAIN_SOURCE_DIR}/
        DESTINATION ${PROJECT_INCLUDE_BINARY_DIR}/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h"
    )
    
    # Project resources installation
    install(
        DIRECTORY ${PROJECT_RESOURCES_MAIN_SOURCE_DIR}/
        DESTINATION ${PROJECT_LIBRARY_BINARY_DIR}
    )
endfunction(install_process)
