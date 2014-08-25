ENABLE_LANGUAGE(Fortran)
SET (CMAKE_Fortran_COMPILER  gfortran)
set(CMAKE_Fortran_FLAGS "-fno-common -ffixed-line-length-132")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(model-f
    couplings.f
    couplings1.f
    couplings2.f
    lha_read.f
    printout.f
    rw_para.f
)
