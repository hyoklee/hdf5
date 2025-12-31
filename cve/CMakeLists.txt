#-----------------------------------------------------------------------------
# CMake configuration for CVE tests
#-----------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.26)
project (HDF5_CVE_TEST C)

#-----------------------------------------------------------------------------
# Define CVE test executables
#-----------------------------------------------------------------------------

# CVE-2025-44904 test
add_executable (cve_2025_44904 ${CMAKE_CURRENT_SOURCE_DIR}/cve_2025_44904.c)

target_include_directories (cve_2025_44904
    PRIVATE "${HDF5_SRC_INCLUDE_DIRS};${HDF5_SRC_BINARY_DIR};${HDF5_TEST_SOURCE_DIR};${HDF5_TEST_BINARY_DIR};$<$<BOOL:${HDF5_ENABLE_PARALLEL}>:${MPI_C_INCLUDE_DIRS}>"
)

target_compile_options(cve_2025_44904 PRIVATE "${HDF5_CMAKE_C_FLAGS}")

target_compile_definitions(cve_2025_44904
    PRIVATE
        "${HDF5_TEST_COMPILE_DEFS_PRIVATE}"
        "H5_TEST_EXPRESS_LEVEL_DEFAULT=${H5_TEST_EXPRESS_LEVEL_DEFAULT}"
)

if (NOT BUILD_SHARED_LIBS)
  TARGET_C_PROPERTIES (cve_2025_44904 STATIC)
  target_link_libraries (cve_2025_44904 PRIVATE ${HDF5_TEST_LIB_TARGET} ${HDF5_LIB_TARGET})
else ()
  TARGET_C_PROPERTIES (cve_2025_44904 SHARED)
  target_link_libraries (cve_2025_44904 PRIVATE ${HDF5_TEST_LIBSH_TARGET} ${HDF5_LIBSH_TARGET})
endif ()

set_target_properties (cve_2025_44904 PROPERTIES FOLDER test/cve)

#-----------------------------------------------------------------------------
# Add tests to CTest
#-----------------------------------------------------------------------------
if (HDF5_TEST_SERIAL)
  add_test (
      NAME CVE-2025-44904
      COMMAND "${CMAKE_COMMAND}"
          -D "TEST_EMULATOR=${CMAKE_CROSSCOMPILING_EMULATOR}"
          -D "TEST_PROGRAM=$<TARGET_FILE:cve_2025_44904>"
          -D "TEST_ARGS:STRING="
          -D "TEST_EXPECT=0"
          -D "TEST_OUTPUT=cve_2025_44904.txt"
          -D "TEST_REFERENCE=cve_2025_44904.out"
          -D "TEST_FOLDER=${PROJECT_BINARY_DIR}"
          -P "${HDF_RESOURCES_DIR}/runTest.cmake"
  )
  set_tests_properties (CVE-2025-44904 PROPERTIES
      TIMEOUT 120
      WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
  )
endif ()
