# --------------------------------------------------------------------
# - FindSOF
#
# This module looks for the Service Oriented Framework (SOF) and defines
#    SOF_FOUND        , set to TRUE if the SOF is found
#    SOF_INCLUDE_DIRS , include directories for SOF
#    SOF_LIBRARY_DIRS , link directories for SOF libraries
#    SOF_LIBRARIES    , the SOF libraries
# --------------------------------------------------------------------

# Include directory finding process
if(NOT ${SOF_HOME})
    find_path(
        SOF_HOME
        NAMES
            impl/src/sof/framework/IBundleActivator.h
        PATHS
            ENV PATH
            $ENV{SOF_HOME}
        DOC
            "SOF path directory"
    )
endif(NOT ${SOF_HOME})
set(SOF_INCLUDE_DIRS ${SOF_HOME}/impl/src CACHE PATH "SOF include directory")

# Library finding process
find_library(
    SOF_LIBRARIES
    NAMES
        sof
    PATHS
        $ENV{SOF_HOME}
        ${SOF_HOME}/build
        ${SOF_HOME}/build/impl
    DOC
        "SOF library"
)
string(REGEX REPLACE "/[^/]*$" "" SOF_LIBRARY_DIRS ${SOF_LIBRARIES})

# Handle the QUIETLY and REQUIRED arguments and set SOF_FOUND to TRUE
# if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SOF DEFAULT_MSG
    SOF_INCLUDE_DIRS
    SOF_LIBRARY_DIRS
    SOF_LIBRARIES
)

mark_as_advanced(SOF_INCLUDE_DIRS SOF_LIBRARY_DIRS SOF_LIBRARIES)