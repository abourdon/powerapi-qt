# --------------------------------------------------------------------
# - FindESFCore
#
# This module looks for the ESF core library and defines
#    ESFCore_FOUND        , set to TRUE if the ESFCore is found
#    ESFCore_INCLUDE_DIRS , include directories for ESFCore
#    ESFCore_LIBRARY_DIRS , link directories for ESFCore libraries
#    ESFCore_LIBRARIES    , the ESFCore libraries
# --------------------------------------------------------------------

# ESF Core target directory
# Include directory finding process
set(ESFCore_INCLUDE_DIRS ${ESFCore_HOME}/include CACHE PATHS "ESFCore include directory")

# Library directory
set(ESFCore_LIBRARY_DIRS ${ESFCore_HOME} CACHE PATHS "ESFCore library directory")

# Library finding process
find_library(
    ESFCore_LIBRARIES
    NAMES
        esf-core
    PATHS
        ${ESFCore_LIBRARY_DIRS}
    DOC
        "ESFCore library"
)

# Handle the QUIETLY and REQUIRED arguments and set PROCPS_FOUND to TRUE
# if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ESFCore DEFAULT_MSG
    ESFCore_INCLUDE_DIRS
    ESFCore_LIBRARY_DIRS
    ESFCore_LIBRARIES
)

mark_as_advanced(ESFCore_INCLUDE_DIRS ESFCore_LIBRARY_DIRS ESFCore_LIBRARIES)
