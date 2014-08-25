include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/helas)
add_library(process-cpp
    CPPProcess.cc
)
add_subdirectory(helas)
target_link_libraries(process-cpp helas-cpp)
