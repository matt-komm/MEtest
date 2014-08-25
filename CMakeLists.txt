project(MEtest)
cmake_minimum_required(VERSION 2.8.3)
set(CMAKE_CXX_FLAGS "-Wextra -Wall -pedantic -std=c++0x -Wno-unused-parameter"${CMAKE_CXX_FLAGS} )
ENABLE_LANGUAGE(Fortran)
SET (CMAKE_Fortran_COMPILER  gfortran)
set(CMAKE_Fortran_FLAGS "-fno-common -ffixed-line-length-132")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_MODULE_PATH}")
find_package(ROOT)



macro(copy_file_if_changed in_file out_file target)  
    	add_custom_command (
    		TARGET     ${target}
    		POST_BUILD
    		COMMAND    ${CMAKE_COMMAND}
    		ARGS       -E copy_if_different ${in_file} ${out_file}
    		COMMENT "Copying file: ${in_file} to: ${out_file}"
    	)
endmacro(copy_file_if_changed)

add_subdirectory(cpp)
add_subdirectory(fortran)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp/helas
    ${CMAKE_CURRENT_SOURCE_DIR}/fortran
    ${CMAKE_CURRENT_SOURCE_DIR}/fortran/DHELAS
    ${CMAKE_CURRENT_SOURCE_DIR}/fortran/MODEL
    ${ROOT_INCLUDE_DIR}
)

add_executable(test
    test.cpp
    fortran/interface.f
)
target_link_libraries(test helas-cpp process-cpp model-f helas-f process-f ${ROOT_LIBRARIES})

add_executable(test-cpp-sa
    check_sa.cpp
)
target_link_libraries(test-cpp-sa helas-cpp process-cpp)

add_executable(test-f-sa
    check_sa.f
)
target_link_libraries(test-f-sa model-f helas-f process-f)

copy_file_if_changed(${CMAKE_CURRENT_SOURCE_DIR}/param_card.dat ${CMAKE_CURRENT_BINARY_DIR}/param_card.dat test) 
copy_file_if_changed(${CMAKE_CURRENT_SOURCE_DIR}/testevents.lhe ${CMAKE_CURRENT_BINARY_DIR}/testevents.lhe test)
copy_file_if_changed(${CMAKE_CURRENT_SOURCE_DIR}/ident_card.dat ${CMAKE_CURRENT_BINARY_DIR}/ident_card.dat test) 


 
