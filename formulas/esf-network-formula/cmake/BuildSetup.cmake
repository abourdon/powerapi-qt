# --------------------------------------------------------------------
# Build setup configuration file
#
# Thanks to this, you could put your specific library home path
#
# This file should be filled in order to generate the CMakeCache.txt file.
# Note that all the necesary platform dependency variables are displayed below, so
# DO NOT edit the CMakeCache.txt file manually!
# --------------------------------------------------------------------

# The ESF bundle name
set(
  ESF_BUNDLE_NAME
  esf-network-formula
  CACHE STRINGS
  "The ESF bundle name"
)

# The Software Oriented Framework (SOF) variable home path
set(
	SOF_HOME
	/home/abourdon/lib/sof/sof_1.2_11050
	CACHE PATH
	"The SOF home path"
)

# The ESF Core home path
set(
    ESFCore_HOME
    /home/abourdon/dev/esf/esf-lib/core/esf-core-build
    CACHE PATH
    "The ESF core library home path"
)

# The ESF Network Sensor home path
set(
    ESFNetworkSensor_HOME
    /home/abourdon/dev/esf/esf-lib/sensors/esf-network-sensor-build
    CACHE PATH
    "The ESF Network Sensor library home path"
)
