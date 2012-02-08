# -*- mode: cmake; -*-
set(flukso_getvalues_src flukso-getvalues.cpp)
set(flukso_archive_src flukso-archive.cpp)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(flukso-getvalues ${flukso_getvalues_src})
add_executable(flukso-archive ${flukso_archive_src})

# todo: replace klio reference with klio module functions
# Link the executable 
target_link_libraries(flukso-getvalues flukso 
  ${CURL_LIBRARIES_SHARED} ${POPT_LIBRARIES} ${JSON_LIBRARIES} ${Boost_LIBRARIES})
target_link_libraries(flukso-archive flukso ${KLIO_LIBRARIES} 
  ${CURL_LIBRARIES_SHARED} ${SQLITE3_LIBRARIES} ${JSON_LIBRARIES} ${Boost_LIBRARIES})

# add programs to the install target - do not install the hashbench benchmark program.
INSTALL(PROGRAMS 
  ${CMAKE_CURRENT_BINARY_DIR}/flukso-getvalues
  ${CMAKE_CURRENT_BINARY_DIR}/flukso-archive
  DESTINATION bin)

