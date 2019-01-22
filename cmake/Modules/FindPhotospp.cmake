set(TEST_PHOTOSPP_ROOT_DIR  "" ${PHOTOSPP_ROOT_DIR})
IF(TEST_PHOTOSPP_ROOT_DIR STREQUAL "")
IF(DEFINED ENV{PHOTOSPP_ROOT_DIR})
set(PHOTOSPP_ROOT_DIR  $ENV{PHOTOSPP_ROOT_DIR})
else()
set(PHOTOSPP_ROOT_DIR  "/usr")
endif()
endif()
find_path(PHOTOSPP_INCLUDE_DIR Photos/Photos.h
          HINTS $ENV{PHOTOSPP_ROOT_DIR}/include ${PHOTOSPP_ROOT_DIR}/include NO_DEFAULT_PATH)

find_library(PHOTOSPP_CxxInterface_LIBRARY NAMES PhotosCxxInterface
             HINTS $ENV{PHOTOSPP_ROOT_DIR}/lib ${PHOTOSPP_ROOT_DIR}/lib
             HINTS $ENV{PHOTOSPP_ROOT_DIR}/lib64 ${PHOTOSPP_ROOT_DIR}/lib64
             )

find_library(PHOTOSPP_Fortran_LIBRARY NAMES PhotosFortran
             HINTS $ENV{PHOTOSPP_ROOT_DIR}/lib ${PHOTOSPP_ROOT_DIR}/lib
             HINTS $ENV{PHOTOSPP_ROOT_DIR}/lib64 ${PHOTOSPP_ROOT_DIR}/lib64
             )

#This is for PHOTOS3.6x
find_library(PHOTOSPP_LIBRARY NAMES Photospp
             HINTS $ENV{PHOTOSPP_ROOT_DIR}/lib ${PHOTOSPP_ROOT_DIR}/lib
             HINTS $ENV{PHOTOSPP_ROOT_DIR}/lib64 ${PHOTOSPP_ROOT_DIR}/lib64
             )

find_library(PHOTOSPP_HEPEVT_LIBRARY NAMES PhotosppHEPEVT
             HINTS $ENV{PHOTOSPP_ROOT_DIR}/lib ${PHOTOSPP_ROOT_DIR}/lib
             HINTS $ENV{PHOTOSPP_ROOT_DIR}/lib64 ${PHOTOSPP_ROOT_DIR}/lib64
             )

find_library(PHOTOSPP_HEPMC_LIBRARY NAMES PhotosppHepMC
             HINTS $ENV{PHOTOSPP_ROOT_DIR}/lib ${PHOTOSPP_ROOT_DIR}/lib
             HINTS $ENV{PHOTOSPP_ROOT_DIR}/lib64 ${PHOTOSPP_ROOT_DIR}/lib64
             )


set(PHOTOSPP_INCLUDE_DIRS ${PHOTOSPP_INCLUDE_DIR})
if (PHOTOSPP_LIBRARY  AND  PHOTOSPP_HEPMC_LIBRARY)
set(PHOTOSPP_LIBRARIES ${PHOTOSPP_LIBRARY} ${PHOTOSPP_HEPEVT_LIBRARY}  )
set(PHOTOSPP_HEPMC2_LIBRARIES  ${PHOTOSPP_HEPMC_LIBRARY}   )
else()
if (PHOTOSPP_CxxInterface_LIBRARY)
set(PHOTOSPP_LIBRARIES ${PHOTOSPP_CxxInterface_LIBRARY} ${PHOTOSPP_Fortran_LIBRARY})
set(PHOTOSPP_HEPMC2_LIBRARIES  ${PHOTOSPP_CxxInterface_LIBRARY}  )
endif()
endif()

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PHOTOSPP DEFAULT_MSG PHOTOSPP_INCLUDE_DIR PHOTOSPP_LIBRARIES)

mark_as_advanced(PHOTOSPP_FOUND PHOTOSPP_INCLUDE_DIR )
