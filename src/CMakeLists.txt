# -*- mode: cmake; -*-
set(flukso_getvalues_src flukso-getvalues.cpp)
set(flukso_archive_src flukso-archive.cpp)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(flukso-getvalues ${flukso_getvalues_src})
add_executable(flukso-archive ${flukso_archive_src})

# TODO: Proper include for libklio
# TODO: Use Boost::ASIO instead of curl
# Link the executable 
target_link_libraries(flukso-getvalues flukso 
  ${CURL_LIBRARY} 
  gss
  ssl
  crypto
  rtmp
  z
  ldap
  gnutls
  ${POPT_LIBRARIES} ${JSON_LIBRARIES} ${Boost_LIBRARIES})

target_link_libraries(flukso-archive flukso ${KLIO_LIBRARIES} 
  ${CURL_LIBRARY} 
  gss
  ssl
  crypto
  rtmp
  z
  ldap
  gnutls
  ${SQLITE3_LIBRARIES} ${JSON_LIBRARIES} ${Boost_LIBRARIES})

# add programs to the install target - do not install the hashbench benchmark program.
INSTALL(PROGRAMS 
  ${CMAKE_CURRENT_BINARY_DIR}/flukso-getvalues
  ${CMAKE_CURRENT_BINARY_DIR}/flukso-archive
  DESTINATION bin)

