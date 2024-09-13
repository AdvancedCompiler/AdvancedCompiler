#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "clFFT" for configuration "Release"
set_property(TARGET clFFT APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(clFFT PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "/opt/AMDAPPSDK-3.0/lib/x86_64/libOpenCL.so;dl"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib64/libclFFT.so.2.12.2"
  IMPORTED_SONAME_RELEASE "libclFFT.so.2"
  )

list(APPEND _IMPORT_CHECK_TARGETS clFFT )
list(APPEND _IMPORT_CHECK_FILES_FOR_clFFT "${_IMPORT_PREFIX}/lib64/libclFFT.so.2.12.2" )

# Import target "StatTimer" for configuration "Release"
set_property(TARGET StatTimer APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(StatTimer PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "/opt/AMDAPPSDK-3.0/lib/x86_64/libOpenCL.so;-lrt"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib64/libStatTimer.so.2.12.2"
  IMPORTED_SONAME_RELEASE "libStatTimer.so.2"
  )

list(APPEND _IMPORT_CHECK_TARGETS StatTimer )
list(APPEND _IMPORT_CHECK_FILES_FOR_StatTimer "${_IMPORT_PREFIX}/lib64/libStatTimer.so.2.12.2" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
