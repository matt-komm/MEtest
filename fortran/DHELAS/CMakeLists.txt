ENABLE_LANGUAGE(Fortran)
SET (CMAKE_Fortran_COMPILER  gfortran)
set(CMAKE_Fortran_FLAGS "-fno-common -ffixed-line-length-132")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(helas-f
    aloha_functions.f
    FFV1_0.f
    FFV1_1.f
    FFV1_2.f
    FFV1P0_3.f
    FFV2_1.f
    FFV2_2.f
    FFV2_3.f
    VVV1P0_1.f
)
