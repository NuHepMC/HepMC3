set(TEST_MCTESTER_ROOT_DIR  "" ${MCTESTER_ROOT_DIR})
IF(TEST_MCTESTER_ROOT_DIR STREQUAL "")
IF(DEFINED ENV{MCTESTER_ROOT_DIR})
set(MCTESTER_ROOT_DIR  $ENV{MCTESTER_ROOT_DIR})
else()
set(MCTESTER_ROOT_DIR  "/usr")
endif()
endif()
find_path(MCTESTER_INCLUDE_DIR HepMCEvent.H
          HINTS $ENV{MCTESTER_ROOT_DIR}/include ${MCTESTER_ROOT_DIR}/include)

find_library(MCTESTER_LIBRARY NAMES MCTester
             HINTS $ENV{MCTESTER_ROOT_DIR}/lib ${MCTESTER_ROOT_DIR}/lib
             HINTS $ENV{MCTESTER_ROOT_DIR}/lib64 ${MCTESTER_ROOT_DIR}/lib64
             )


find_library(MCTESTER_LIBRARY_HEPEvent NAMES HEPEvent
             HINTS $ENV{MCTESTER_ROOT_DIR}/lib ${MCTESTER_ROOT_DIR}/lib
             HINTS $ENV{MCTESTER_ROOT_DIR}/lib64 ${MCTESTER_ROOT_DIR}/lib64
             )

find_library(MCTESTER_LIBRARY_HepMCEvent NAMES HepMCEvent
             HINTS $ENV{MCTESTER_ROOT_DIR}/lib ${MCTESTER_ROOT_DIR}/lib
             HINTS $ENV{MCTESTER_ROOT_DIR}/lib64 ${MCTESTER_ROOT_DIR}/lib64
             )


set(MCTESTER_INCLUDE_DIRS ${MCTESTER_INCLUDE_DIR})
set(MCTESTER_LIBRARIES ${MCTESTER_LIBRARY} ${MCTESTER_LIBRARY_HEPEvent} ${MCTESTER_LIBRARY_HepMCEvent})

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(MCTESTER DEFAULT_MSG MCTESTER_INCLUDE_DIR )

mark_as_advanced(MCTESTER_FOUND MCTESTER_INCLUDE_DIR )