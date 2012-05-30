# --------------------------------------------------------------------
# - FindESFNetworkSensor
#
# This module looks for the ESF Network Sensor library and defines
#    ESFNetworkSensor_FOUND        , set to TRUE if the ESFNetworkSensor is found
#    ESFNetworkSensor_INCLUDE_DIRS , include directories for ESFNetworkSensor
#    ESFNetworkSensor_LIBRARY_DIRS , link directories for ESFNetworkSensor libraries
#    ESFNetworkSensor_LIBRARIES    , the ESFNetworkSensor libraries
# --------------------------------------------------------------------

# ESF Network Sensor target directory
# Include directory finding process
set(ESFNetworkSensor_INCLUDE_DIRS ${ESFNetworkSensor_HOME}/include CACHE PATHS "ESFNetworkSensor include directory")

# Library directory
set(ESFNetworkSensor_LIBRARY_DIRS ${ESFNetworkSensor_HOME} CACHE PATHS "ESFNetworkSensor library directory")

# Library finding process
find_library(
    ESFNetworkSensor_LIBRARIES
    NAMES
        esf-network-sensor
    PATHS
        ${ESFNetworkSensor_LIBRARY_DIRS}
    DOC
        "ESFNetworkSensor library"
)

# Handle the QUIETLY and REQUIRED arguments and set PROCPS_FOUND to TRUE
# if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ESFNetworkSensor DEFAULT_MSG
    ESFNetworkSensor_INCLUDE_DIRS
    ESFNetworkSensor_LIBRARY_DIRS
    ESFNetworkSensor_LIBRARIES
)

mark_as_advanced(ESFNetworkSensor_INCLUDE_DIRS ESFNetworkSensor_LIBRARY_DIRS ESFNetworkSensor_LIBRARIES)
