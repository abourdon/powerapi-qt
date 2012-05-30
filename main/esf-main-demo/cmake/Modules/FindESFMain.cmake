# --------------------------------------------------------------------
# - FindESFMain
#
# This module looks for the ESF Main library and defines
#    ESFMain_FOUND        , set to TRUE if the ESFMain is found
#    ESFMain_INCLUDE_DIRS , include directories for ESFMain
#    ESFMain_LIBRARY_DIRS , link directories for ESFMain libraries
#    ESFMain_LIBRARIES    , the ESFMain libraries
# --------------------------------------------------------------------

# Include directory finding process
set(ESFMain_INCLUDE_DIRS ${ESFMain_HOME}/include CACHE PATHS "ESFMain include directory")

# Library directory
set(ESFMain_LIBRARY_DIRS ${ESFMain_HOME} CACHE PATHS "ESFMain library directory")

# Library finding process
find_library(
    ESFMain_LIBRARIES
    NAMES
        esf-main
    PATHS
        ${ESFMain_LIBRARY_DIRS}
    DOC
        "ESFMain library"
)

# Handle the QUIETLY and REQUIRED arguments and set PROCPS_FOUND to TRUE
# if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ESFMain DEFAULT_MSG
    ESFMain_INCLUDE_DIRS
    ESFMain_LIBRARY_DIRS
    ESFMain_LIBRARIES
)

mark_as_advanced(ESFMain_INCLUDE_DIRS ESFMain_LIBRARY_DIRS ESFMain_LIBRARIES)
