add_subdirectory(DHELAS)
add_subdirectory(MODEL)

ENABLE_LANGUAGE(Fortran)
SET (CMAKE_Fortran_COMPILER  gfortran)
set(CMAKE_Fortran_FLAGS "-fno-common -ffixed-line-length-132")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(process-f
    matrix.f
)
target_link_libraries(process-f model-f helas-f)
