# --------------------------------------------------------------------
# - FindESFNetworkFormula
#
# This module looks for the ESF Network Formula library and defines
#    ESFNetworkFormula_FOUND        , set to TRUE if the ESFNetworkFormula is found
#    ESFNetworkFormula_INCLUDE_DIRS , include directories for ESFNetworkFormula
#    ESFNetworkFormula_LIBRARY_DIRS , link directories for ESFNetworkFormula libraries
#    ESFNetworkFormula_LIBRARIES    , the ESFNetworkFormula libraries
# --------------------------------------------------------------------

# ESF Network Formula target directory
# Include directory finding process
set(ESFNetworkFormula_INCLUDE_DIRS ${ESFNetworkFormula_HOME}/include CACHE PATHS "ESFNetworkFormula include directory")

# Library directory
set(ESFNetworkFormula_LIBRARY_DIRS ${ESFNetworkFormula_HOME} CACHE PATHS "ESFNetworkFormula library directory")

# Library finding process
find_library(
    ESFNetworkFormula_LIBRARIES
    NAMES
        esf-network-formula
    PATHS
        ${ESFNetworkFormula_LIBRARY_DIRS}
    DOC
        "ESFNetworkFormula library"
)

# Handle the QUIETLY and REQUIRED arguments and set PROCPS_FOUND to TRUE
# if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ESFNetworkFormula DEFAULT_MSG
    ESFNetworkFormula_INCLUDE_DIRS
    ESFNetworkFormula_LIBRARY_DIRS
    ESFNetworkFormula_LIBRARIES
)

mark_as_advanced(ESFNetworkFormula_INCLUDE_DIRS ESFNetworkFormula_LIBRARY_DIRS ESFNetworkFormula_LIBRARIES)
