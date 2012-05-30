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
  esf-core
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

# The PROCPS variable home path
set(
	PROCPS_HOME
	/home/abourdon/lib/procps
	CACHE PATH
	"The PROCPS home path"
)
