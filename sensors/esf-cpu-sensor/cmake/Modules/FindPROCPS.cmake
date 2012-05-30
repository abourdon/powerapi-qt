# --------------------------------------------------------------------
# - FindPROCPS
#
# This module looks for the PROCPS software and defines
#    PROCPS_FOUND        , set to TRUE if the PROCPS is found
#    PROCPS_INCLUDE_DIRS , include directories for PROCPS
#    PROCPS_LIBRARY_DIRS , link directories for PROCPS libraries
#    PROCPS_LIBRARIES    , the PROCPS libraries
# --------------------------------------------------------------------

# Include directory finding process
set(PROCPS_INCLUDE_DIRS ${PROCPS_HOME} CACHE PATHS "PROCPS include directory")

# Library finding process
find_library(
    PROCPS_LIBRARIES
    NAMES
        proc
    PATHS
        $ENV{PROCPS_HOME}/proc
        ${PROCPS_HOME}/proc
    DOC
        "PROCPS library"
)
string(REGEX REPLACE "/[^/]*$" "" PROCPS_LIBRARY_DIRS ${PROCPS_LIBRARIES})

# Handle the QUIETLY and REQUIRED arguments and set PROCPS_FOUND to TRUE
# if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PROCPS DEFAULT_MSG
    PROCPS_INCLUDE_DIRS
    PROCPS_LIBRARY_DIRS
    PROCPS_LIBRARIES
)

mark_as_advanced(PROCPS_INCLUDE_DIRS PROCPS_LIBRARY_DIRS PROCPS_LIBRARIES)