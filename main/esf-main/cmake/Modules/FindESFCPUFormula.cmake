# --------------------------------------------------------------------
# - FindESFCPUFormula
#
# This module looks for the ESF CPU Formula library and defines
#    ESFCPUFormula_FOUND        , set to TRUE if the ESFCPUFormula is found
#    ESFCPUFormula_INCLUDE_DIRS , include directories for ESFCPUFormula
#    ESFCPUFormula_LIBRARY_DIRS , link directories for ESFCPUFormula libraries
#    ESFCPUFormula_LIBRARIES    , the ESFCPUFormula libraries
# --------------------------------------------------------------------

# ESF Core target directory
# Include directory finding process
set(ESFCPUFormula_INCLUDE_DIRS ${ESFCPUFormula_HOME}/include CACHE PATHS "ESFCPUFormula include directory")

# Library directory
set(ESFCPUFormula_LIBRARY_DIRS ${ESFCPUFormula_HOME} CACHE PATHS "ESFCPUFormula library directory")

# Library finding process
find_library(
    ESFCPUFormula_LIBRARIES
    NAMES
        esf-cpu-formula
    PATHS
        ${ESFCPUFormula_LIBRARY_DIRS}
    DOC
        "ESFCPUFormula library"
)

# Handle the QUIETLY and REQUIRED arguments and set PROCPS_FOUND to TRUE
# if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ESFCPUFormula DEFAULT_MSG
    ESFCPUFormula_INCLUDE_DIRS
    ESFCPUFormula_LIBRARY_DIRS
    ESFCPUFormula_LIBRARIES
)

mark_as_advanced(ESFCPUFormula_INCLUDE_DIRS ESFCPUFormula_LIBRARY_DIRS ESFCPUFormula_LIBRARIES)
