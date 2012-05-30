# --------------------------------------------------------------------
# - FindESFCPUSensor
#
# This module looks for the ESF CPU Sensor library and defines
#    ESFCPUSensor_FOUND        , set to TRUE if the ESFCPUSensor is found
#    ESFCPUSensor_INCLUDE_DIRS , include directories for ESFCPUSensor
#    ESFCPUSensor_LIBRARY_DIRS , link directories for ESFCPUSensor libraries
#    ESFCPUSensor_LIBRARIES    , the ESFCPUSensor libraries
# --------------------------------------------------------------------

# ESF Core target directory
# Include directory finding process
set(ESFCPUSensor_INCLUDE_DIRS ${ESFCPUSensor_HOME}/include CACHE PATHS "ESFCPUSensor include directory")

# Library directory
set(ESFCPUSensor_LIBRARY_DIRS ${ESFCPUSensor_HOME} CACHE PATHS "ESFCPUSensor library directory")

# Library finding process
find_library(
    ESFCPUSensor_LIBRARIES
    NAMES
        esf-cpu-sensor
    PATHS
        ${ESFCPUSensor_LIBRARY_DIRS}
    DOC
        "ESFCPUSensor library"
)

# Handle the QUIETLY and REQUIRED arguments and set PROCPS_FOUND to TRUE
# if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ESFCPUSensor DEFAULT_MSG
    ESFCPUSensor_INCLUDE_DIRS
    ESFCPUSensor_LIBRARY_DIRS
    ESFCPUSensor_LIBRARIES
)

mark_as_advanced(ESFCPUSensor_INCLUDE_DIRS ESFCPUSensor_LIBRARY_DIRS ESFCPUSensor_LIBRARIES)
