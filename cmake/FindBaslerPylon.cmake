# - Try to find Pylon
# Once done this will define
#  PYLON_FOUND - System has Pylon
#  PYLON_INCLUDE_DIRS - The Pylon include directories
#  PYLON_LIBRARIES - The libraries needed to use Pylon

set( PYLON_LIBRARY_PATH "/opt/pylon5/lib64" )

FIND_PATH(	PYLON_INCLUDE_DIR pylon/PylonBase.h
			PATHS
			/opt/pylon5/include
			"$ENV{PYLON_ROOT}/include"
)

FIND_LIBRARY(	PYLONBASE_LIBRARY 
				NAMES 
				libpylonbase.so 
				PATHS
				${PYLON_LIBRARY_PATH}
)

FIND_LIBRARY(	PYLON_UTILITY_LIBRARY 
				NAMES 
				libpylonutility.so 
				PATHS
				${PYLON_LIBRARY_PATH}
)

FIND_LIBRARY(	GenApi_gcc_LIBRARY 
				NAMES 
				libGenApi_gcc_v3_0_Basler_pylon_v5_0.so
				PATHS
				${PYLON_LIBRARY_PATH}
)

set( XERCES-C_LIBRARY "" )
FIND_LIBRARY(	GCBase_LIBRARY 
				NAMES 
				libGCBase_gcc_v3_0_Basler_pylon_v5_0.so
				PATHS
				${PYLON_LIBRARY_PATH}
)

if( NOT GCBase_LIBRARY)
    set(GCBase_LIBRARY "")
endif(NOT GCBase_LIBRARY)

if( NOT GenApi_gcc_LIBRARY)
    set(GenApi_gcc_LIBRARY "")
endif(NOT GenApi_gcc_LIBRARY)

set(PYLON_LIBRARIES  ${PYLONBASE_LIBRARY} ${GCBase_LIBRARY} ${PYLON_UTILITY_LIBRARY} ${GenApi_gcc_LIBRARY})
set(PYLON_INCLUDE_DIRS ${PYLON_INCLUDE_DIR})

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(PYLON DEFAULT_MSG
  PYLON_INCLUDE_DIR
  PYLON_LIBRARY)

mark_as_advanced(PYLON_INCLUDE_DIR PYLON_LIBRARIES)
