macro( hepmc_test testname )
  message( STATUS "HepMC3 test: building ${testname} for ${testname}" )
  find_file( ${testname}_source ${testname}.cc ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} )
  ADD_EXECUTABLE(${testname} ${${testname}_source}   ${ARGN} )
  target_include_directories(${testname} BEFORE
  PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src   ${CMAKE_CURRENT_SOURCE_DIR}/../include/)
  target_link_libraries(${testname} PUBLIC  PRIVATE HepMC3 )
  set(srcdir ${CMAKE_CURRENT_SOURCE_DIR} )
  set(builddir ${CMAKE_CURRENT_BINARY_DIR} )
  add_test( ${testname} ${CMAKE_CURRENT_BINARY_DIR}/${testname} )
  SET_TESTS_PROPERTIES( ${testname} PROPERTIES ENVIRONMENT "PATH=${PROJECT_BINARY_DIR}/outputs/${CMAKE_INSTALL_LIBDIR}/;$ENV{PATH}")
  file(GLOB INPUT${testname}  "${CMAKE_CURRENT_SOURCE_DIR}/input${testname}*" )
  file(COPY ${INPUT${testname}} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  string(REPLACE "test" "" ${testname} name)
  file(GLOB INPUT${name}  "${CMAKE_CURRENT_SOURCE_DIR}/input${name}*" )
  file(COPY ${INPUT${name}} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endmacro( hepmc_test )

macro( hepmc_root_test testname )
  message( STATUS "HepMC3 test: building ROOT test ${testname} " )
  find_file( ${testname}_source ${testname}.cc ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} )
  ADD_EXECUTABLE(${testname} ${${testname}_source}  ${ARGN} )
  target_include_directories(${testname} BEFORE
  PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src   ${CMAKE_CURRENT_SOURCE_DIR}/../include/ ${CMAKE_CURRENT_SOURCE_DIR}/../rootIO/include/ )
  target_link_libraries(${testname} PRIVATE HepMC3 HepMC3rootIO)

  set(srcdir ${CMAKE_CURRENT_SOURCE_DIR} )
  set(builddir ${CMAKE_CURRENT_BINARY_DIR} )
  add_test( ${testname} ${testname} )
  SET_TESTS_PROPERTIES( ${testname} PROPERTIES ENVIRONMENT "PATH=${PROJECT_BINARY_DIR}/outputs/${CMAKE_INSTALL_LIBDIR}/;$ENV{PATH}"
  ENVIRONMENT "LD_LIBRARY_PATH=${PROJECT_BINARY_DIR}/outputs/${CMAKE_INSTALL_LIBDIR}/;$ENV{LD_LIBRARY_PATH}"
  ENVIRONMENT "DYLD_LIBRARY_PATH=${PROJECT_BINARY_DIR}/outputs/${CMAKE_INSTALL_LIBDIR}/;$ENV{DYLD_LIBRARY_PATH}"
  )
  file(GLOB INPUT${testname}  "${CMAKE_CURRENT_SOURCE_DIR}/input${testname}*" )
  file(COPY ${INPUT${testname}} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  string(REPLACE "test" "" ${testname} name)
  file(GLOB INPUT${name}  "${CMAKE_CURRENT_SOURCE_DIR}/input${name}*" )
  file(COPY ${INPUT${name}} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endmacro( hepmc_root_test )


macro( hepmc_protobuf_test testname )
  message( STATUS "HepMC3 test: building protobuf test ${testname} " )
  find_file( ${testname}_source ${testname}.cc ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} )
  ADD_EXECUTABLE(${testname} ${${testname}_source}  ${ARGN} )
  target_include_directories(${testname} BEFORE
  PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src   ${CMAKE_CURRENT_SOURCE_DIR}/../include/ ${CMAKE_CURRENT_SOURCE_DIR}/../protobufIO/include/ )
  target_link_libraries(${testname} PRIVATE HepMC3 HepMC3protobufIO)

  set(srcdir ${CMAKE_CURRENT_SOURCE_DIR} )
  set(builddir ${CMAKE_CURRENT_BINARY_DIR} )
  add_test( ${testname} ${testname} )
  SET_TESTS_PROPERTIES( ${testname} PROPERTIES ENVIRONMENT "PATH=${PROJECT_BINARY_DIR}/outputs/${CMAKE_INSTALL_LIBDIR}/;$ENV{PATH}")
  file(GLOB INPUT${testname}  "${CMAKE_CURRENT_SOURCE_DIR}/input${testname}*" )
  file(COPY ${INPUT${testname}} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  string(REPLACE "test" "" ${testname} name)
  file(GLOB INPUT${name}  "${CMAKE_CURRENT_SOURCE_DIR}/input${name}*" )
  file(COPY ${INPUT${name}} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endmacro( hepmc_protobuf_test )


set( CMAKE_INCLUDE_DIRECTORIES_BEFORE ON )
cmake_policy(SET CMP0057 NEW)

option(HEPMC3_TEST_THREADS   "Use Threads in tests if available" ON)
option(HEPMC3_TEST_HEPMC2    "Use HepMC2 in tests if available" ON)
option(HEPMC3_TEST_VALGRIND  "Use valgrind in tests if available" OFF)
option(HEPMC3_TEST_ZLIB      "Use zlib in tests if available" ON)
option(HEPMC3_TEST_LZMA      "Use lzma in tests if available" ON)
option(HEPMC3_TEST_BZIP2     "Use bzip2 in tests if available" ON)
option(HEPMC3_TEST_ZSTD      "Use zstd in tests if available" ON)

set(HEPMC3_TEST_PACKAGES_LIST "")
if (HEPMC3_TEST_THREADS)
 LIST(APPEND HEPMC3_TEST_PACKAGES_LIST "Threads")
endif()
if (HEPMC3_TEST_HEPMC2)
 LIST(APPEND HEPMC3_TEST_PACKAGES_LIST "HepMC2")
endif()
if (HEPMC3_TEST_VALGRIND)
 LIST(APPEND HEPMC3_TEST_PACKAGES_LIST "valgrind")
endif()
if (HEPMC3_TEST_ZLIB)
 LIST(APPEND HEPMC3_TEST_PACKAGES_LIST "zlib")
endif()
if (HEPMC3_TEST_LZMA)
 LIST(APPEND HEPMC3_TEST_PACKAGES_LIST "lzma")
endif()
if (HEPMC3_TEST_BZIP2)
 LIST(APPEND HEPMC3_TEST_PACKAGES_LIST "bzip2")
endif()
if (HEPMC3_TEST_ZSTD)
 LIST(APPEND HEPMC3_TEST_PACKAGES_LIST "zstd")
endif()
message(STATUS "HepMC3 test: The following packages are enabled for tests HEPMC3_TEST_PACKAGES_LIST=${HEPMC3_TEST_PACKAGES_LIST}" )

file(GLOB INPUTFILES  "${CMAKE_CURRENT_SOURCE_DIR}/*.input" )
file(COPY ${INPUTFILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set( HepMC_tests
        testBoost
        testFourVector
        testMass
        testPrintBug
        testPolarization
        testUnits
        testMultipleCopies
        testWeights
        testLoops
        testDelete
        testSkip1
        testIO1
        testIO3
        testIO6
        testIO7
        testIO8
        testIO11
        testReaderFactory1
        testSingleVertexHepMC2
        testAttributes
        testHEPEVTWrapper1
        testVertexAttributes
         )
set( HepMC_root_tests
        testIO2
        testIO4
        testReaderFactory2
        testRoot300
        testRootTree300
        )

set( HepMC_search_tests

        )
if (WIN32)
  set( HepMC_protobuf_tests )
else()
  set( HepMC_protobuf_tests
        testIO20
        testIO21
        testIO22
        testIO23
        testIO24
        testIO25
        testIO26
        testIO27
        testIO28
        testIO29
        )
endif()

set(srcdir ${CMAKE_CURRENT_SOURCE_DIR} )
if ("Threads" IN_LIST HEPMC3_TEST_PACKAGES_LIST)
  set(THREADS_PREFER_PTHREAD_FLAG ON)
  find_package(Threads)
endif()
if("Threads" IN_LIST HEPMC3_TEST_PACKAGES_LIST AND Threads_FOUND AND NOT (${CMAKE_CXX_COMPILER_ID} MATCHES "PGI") AND NOT (${CMAKE_CXX_COMPILER_ID} MATCHES "NVHPC"))
  message(STATUS "HepMC3 test: Threads library found.  Thread safety tests enabled")
  list( APPEND HepMC_tests "testThreads1" )
  list( APPEND HepMC_tests "testIO10" )
  list( APPEND HepMC_tests "testReaderFactory3" )
  if (HEPMC3_ENABLE_SEARCH)
    list( APPEND HepMC_search_tests "testThreadssearch" )
  endif()
else()
  message(STATUS "HepMC3 test: No threads library found or disabled for compiller with ID ${CMAKE_CXX_COMPILER_ID}. Thread safety tests are disabled")
endif()

set(compress_tests "testIO9")
if ("zlib" IN_LIST HEPMC3_TEST_PACKAGES_LIST)
  find_package(ZLIB)
  if(ZLIB_FOUND)
    message(STATUS "HepMC3 test: ZLIB library found. zlib tests enabled")
    list( APPEND HepMC_tests ${compress_tests} )
  endif()
endif()
if ("lzma" IN_LIST HEPMC3_TEST_PACKAGES_LIST)
  find_package(LibLZMA)
  if(LIBLZMA_FOUND)
    message(STATUS "HepMC3 test: LZMA library found.  lzma tests enabled")
    list( APPEND HepMC_tests ${compress_tests} )
  endif()
endif()
if ("bzip2" IN_LIST HEPMC3_TEST_PACKAGES_LIST)
  find_package(BZip2)
  if(LIBLZMA_FOUND)
    message(STATUS "HepMC3 test: BZip2 library found.  BZip2 tests enabled")
    list( APPEND HepMC_tests ${compress_tests} )
  endif()
endif()
if ("zstd" IN_LIST HEPMC3_TEST_PACKAGES_LIST)
  #find_package(ZSTD)#FIXME!
  if(ZSTD_FOUND)
    message(STATUS "HepMC3 test: Zstd library found.  Zstd tests enabled")
    list( APPEND HepMC_tests ${compress_tests} )
  endif()
endif()

## Here we add the tests
list(REMOVE_DUPLICATES HepMC_tests)
foreach ( test ${HepMC_tests} )
  hepmc_test( ${test} )
  set_tests_properties(${test} PROPERTIES TIMEOUT 2000)  #Relevant for testLoops
endforeach ( test ${HepMC_tests} )

if(HEPMC3_ENABLE_SEARCH )
  foreach ( test ${HepMC_search_tests} )
    hepmc_test( ${test} )
  target_link_libraries(${test} PRIVATE HepMC3search)
  target_include_directories(${test} BEFORE PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR}/../search/include)
  endforeach ( test ${HepMC_search_tests} )
endif()

if(HEPMC3_ENABLE_PROTOBUFIO )
  foreach ( test ${HepMC_protobuf_tests} )
    hepmc_protobuf_test( ${test} )
  target_link_libraries(${test} PRIVATE HepMC3protobufIO)
  target_include_directories(${test} BEFORE PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR}/../protobufIO/include)
  endforeach ( test ${HepMC_protobuf_tests} )
endif()


## Treatment of special needs in the HepMC tests
if(Threads_FOUND AND NOT (${CMAKE_CXX_COMPILER_ID} MATCHES "PGI") AND NOT (${CMAKE_CXX_COMPILER_ID} MATCHES "NVHPC") )
  if(THREADS_HAVE_PTHREAD_ARG)
    target_compile_options(testThreads1 PUBLIC "-pthread")
    target_compile_options(testIO10 PUBLIC "-pthread")
    target_compile_options(testReaderFactory3 PUBLIC "-pthread")
    if (HEPMC3_ENABLE_SEARCH)
     target_compile_options(testThreadssearch PUBLIC "-pthread")
    endif()
  endif()
  if(CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(testThreads1 PUBLIC "${CMAKE_THREAD_LIBS_INIT}")
    target_link_libraries(testIO10 PUBLIC "${CMAKE_THREAD_LIBS_INIT}")
    target_link_libraries(testReaderFactory3 PUBLIC "${CMAKE_THREAD_LIBS_INIT}")
    if (HEPMC3_ENABLE_SEARCH)
     target_link_libraries(testThreadssearch PUBLIC "${CMAKE_THREAD_LIBS_INIT}")
    endif()
  endif()
endif()
if (WIN32)
  if ("zlib" IN_LIST HEPMC3_TEST_PACKAGES_LIST AND ZLIB_FOUND)
     get_filename_component(z ${ZLIB_LIBRARIES} DIRECTORY)
     find_file(zdll NAME zlib.dll PATHS ${z} ${z}/../bin/)
     if (zdll)
       file(COPY ${zdll} DESTINATION ${PROJECT_BINARY_DIR}/outputs/${CMAKE_INSTALL_LIBDIR}/)
     endif()
   endif()
   if ("lzma" IN_LIST HEPMC3_TEST_PACKAGES_LIST AND LIBLZMA_FOUND)
     get_filename_component(l ${LIBLZMA_LIBRARIES} DIRECTORY)
     find_file(lzmadll NAME lzma.dll PATHS ${l} ${l}/../bin/)
     if (lzmadll)
       file(COPY ${lzmadll} DESTINATION ${PROJECT_BINARY_DIR}/outputs/${CMAKE_INSTALL_LIBDIR}/)
     endif()
   endif()
   if ("bzip2" IN_LIST HEPMC3_TEST_PACKAGES_LIST AND BZIP2_FOUND)
     get_filename_component(b ${BZIP2_LIBRARIES} DIRECTORY)
     find_file(bz2dll NAME libbz2.dll PATHS ${b} ${b}/../bin/)
     if (bz2dll)
       file(COPY ${bz2dll} DESTINATION ${PROJECT_BINARY_DIR}/outputs/${CMAKE_INSTALL_LIBDIR}/)
     endif()
   endif()
   #if ("zstd" IN_LIST HEPMC3_TEST_PACKAGES_LIST AND ZSTD_FOUND)
     #get_filename_component(b ${ZSTD_LIBRARIES} DIRECTORY)
     #find_file(zstddll NAME libzstd.dll PATHS ${b} ${b}/../bin/)
     #if (zstddll)
       #file(COPY ${zstddll} DESTINATION ${PROJECT_BINARY_DIR}/outputs/${CMAKE_INSTALL_LIBDIR}/)
     #endif()
   #endif()
endif()

foreach ( ctest ${compress_tests} )
  if ("zlib" IN_LIST HEPMC3_TEST_PACKAGES_LIST AND ZLIB_FOUND)
    target_compile_options(${ctest} PUBLIC "-DHEPMC3_USE_COMPRESSION")
    target_compile_options(${ctest} PUBLIC "-DHEPMC3_Z_SUPPORT=1")
    target_link_libraries(${ctest} PRIVATE "${ZLIB_LIBRARIES}" )
    target_include_directories(${ctest} PRIVATE "${ZLIB_INCLUDE_DIRS}" )
  endif()
  if ("lzma" IN_LIST HEPMC3_TEST_PACKAGES_LIST AND LIBLZMA_FOUND)
    target_compile_options(${ctest} PUBLIC "-DHEPMC3_USE_COMPRESSION")
    target_compile_options(${ctest} PUBLIC "-DHEPMC3_LZMA_SUPPORT=1")
    target_link_libraries(${ctest} PRIVATE "${LIBLZMA_LIBRARIES}" )
    target_include_directories(${ctest} PRIVATE "${LIBLZMA_INCLUDE_DIRS}" )
  endif()
  if ("bzip2" IN_LIST HEPMC3_TEST_PACKAGES_LIST AND BZIP2_FOUND)
    target_compile_options(${ctest} PUBLIC "-DHEPMC3_USE_COMPRESSION")
    target_compile_options(${ctest} PUBLIC "-DHEPMC3_BZ2_SUPPORT=1")
    target_link_libraries(${ctest} PRIVATE "${BZIP2_LIBRARIES}" )
    target_include_directories(${ctest} PRIVATE "${BZIP2_INCLUDE_DIRS}" )
  endif()
  #if ("zstd" IN_LIST HEPMC3_TEST_PACKAGES_LIST AND ZSTD_FOUND)
    #target_compile_options(${ctest} PUBLIC "-DHEPMC3_USE_COMPRESSION")
    #target_compile_options(${ctest} PUBLIC "-DHEPMC3_ZSTD_SUPPORT=1")
    #target_link_libraries(${ctest} PRIVATE "${ZSTD_LIBRARIES}" )
    #target_include_directories(${ctest} PRIVATE "${ZSTD_INCLUDE_DIRS}" )
  #endif()
endforeach ( ctest ${compress_tests} )
#So far the test with ROOT have issues on WIN32
if(HEPMC3_ENABLE_ROOTIO AND (NOT WIN32) )
  foreach ( test ${HepMC_root_tests} )
    hepmc_root_test( ${test} )
  endforeach ( test ${HepMC_root_tests} )
  target_link_libraries(testIO4 PRIVATE ${ROOT_Hist_LIBRARY})
endif()


set( convert_tests )


if ("HepMC2" IN_LIST HEPMC3_TEST_PACKAGES_LIST)
  find_package(HepMC2 QUIET)
endif()

if(NOT HepMC2_FOUND)
  message(STATUS "HepMC3 test: HEPMC2 package not found or disabled. Please check if HEPMC2_ROOT_DIR is set properly.")
else()

  list( APPEND convert_tests "testConvert1" )
  list( APPEND convert_tests "testConvert2" )
endif()


macro( hepmc_convert_test testname )
  message( STATUS "HepMC3 test: building Convert test ${testname} with HEPMC2" )
  find_file( ${testname}_source ${testname}.cc ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} )
  message( STATUS "HepMC3 test: building Convert test ${testname} ${${testname}_source} with HEPMC2" )
  ADD_EXECUTABLE(convert_${testname} ${${testname}_source}  ${ARGN} )
  target_include_directories(convert_${testname} BEFORE
  PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src   ${CMAKE_CURRENT_SOURCE_DIR}/../include/   "${PROJECT_SOURCE_DIR}/interfaces/HepMCCompatibility/include" )
  target_link_libraries(convert_${testname} PRIVATE HepMC2::HepMC2  HepMC3  )
  set(srcdir ${CMAKE_CURRENT_SOURCE_DIR} )
  set(builddir ${CMAKE_CURRENT_BINARY_DIR} )
  add_test( convert_${testname} convert_${testname} )
  SET_TESTS_PROPERTIES(  convert_${testname} PROPERTIES ENVIRONMENT "PATH=${PROJECT_BINARY_DIR}/outputs/${CMAKE_INSTALL_LIBDIR}/;$ENV{PATH}")
  file(GLOB INPUTconvert_${testname}  "${CMAKE_CURRENT_SOURCE_DIR}/input${testname}*" )
  file(COPY ${INPUTconvert_${testname}} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  string(REPLACE "test" "" ${testname} name)
  file(GLOB INPUTconvert_${name}  "${CMAKE_CURRENT_SOURCE_DIR}/input${name}*" )
  file(COPY ${INPUTconvert_${name}} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endmacro( hepmc_convert_test )

foreach ( test ${convert_tests} )
  hepmc_convert_test( ${test} )
endforeach ( test ${convert_tests} )


#One should use something else for Windows/BSD/MAC


if ("valgrind" IN_LIST HEPMC3_TEST_PACKAGES_LIST)
  find_program( MEMORYCHECK_COMMAND valgrind )
endif()
if(MEMORYCHECK_COMMAND)
  message(STATUS "HepMC3 test: valgrind package found in ${MEMORYCHECK_COMMAND}.  memory check tests enabled.")
  set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full --error-exitcode=1 --default-suppressions=yes --gen-suppressions=all" )
  if (${CMAKE_CXX_COMPILER_ID} MATCHES "Intel")
     file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/intelHepMC3.supp" "{\n<HepMC3_at_Linux_with_Intel_1>\nMemcheck:Addr32\nfun:__intel_*\n}\n{\n<HepMC3_at_Linux_with_Intel_2>\nMemcheck:Cond\nfun:*strchr\n}\n"  )
     set( MEMORYCHECK_COMMAND_OPTIONS  "${MEMORYCHECK_COMMAND_OPTIONS} --suppressions=${CMAKE_CURRENT_BINARY_DIR}/IntelHepMC3.supp")
  endif()
elseif()
  message(STATUS "HepMC3 test: valgrind package not found or disabled.  memory check tests disabled.")
endif()


macro(add_memcheck_test binaryname )
  set(memcheck_command "${MEMORYCHECK_COMMAND} ${MEMORYCHECK_COMMAND_OPTIONS}")
  separate_arguments(memcheck_command)
  add_test(memcheck_${binaryname} ${memcheck_command} ./${binaryname} ${ARGN})
  SET_TESTS_PROPERTIES( memcheck_${binaryname} PROPERTIES ENVIRONMENT "PATH=${PROJECT_BINARY_DIR}/outputs/${CMAKE_INSTALL_LIBDIR}/;$ENV{PATH}")
  file(GLOB INPUTmemcheck_${binaryname}  "${CMAKE_CURRENT_SOURCE_DIR}/input${binaryname}*" )
  file(COPY ${INPUTmemcheck_${binaryname}} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  string(REPLACE "test" "" ${binaryname} name)
  file(GLOB INPUTmemcheck_${name}  "${CMAKE_CURRENT_SOURCE_DIR}/input${name}*" )
  file(COPY ${INPUTmemcheck_${name}} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endmacro(add_memcheck_test)


if(MEMORYCHECK_COMMAND)
  set( HepMC_memcheck_tests ${HepMC_tests} )
  if(HEPMC3_ENABLE_PROTOBUFIO )
    set( HepMC_memcheck_tests ${HepMC_memcheck_tests} ${HepMC_protobuf_tests} )
  endif()
  list(REMOVE_ITEM HepMC_memcheck_tests testFourVector )
#The story behind is complicated. It seems that on some platforms valgind dislikes the comparison of infinities.
  foreach ( test ${HepMC_memcheck_tests} )
    add_memcheck_test( ${test} )
    set_tests_properties(memcheck_${test} PROPERTIES DEPENDS ${test})
  endforeach ( test ${HepMC_memcheck_tests} )
endif()

