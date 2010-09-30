# -*- mode: cmake; -*-
set(flukso_getvalues_src flukso-getvalues.cpp)

include_directories(${CMAKE_SOURCE_DIR}/libflukso ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(flukso-getvalues ${flukso_getvalues_src})

# Link the executable 
target_link_libraries(flukso-getvalues flukso ${CURL_LIBRARIES_SHARED} ${POPT_LIBRARIES} ${JSON_LIBRARIES})

# add programs to the install target - do not install the hashbench benchmark program.
INSTALL(PROGRAMS 
  ${CMAKE_CURRENT_BINARY_DIR}/flukso-getvalues
  DESTINATION bin)

