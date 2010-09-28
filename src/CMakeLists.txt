# -*- mode: cmake; -*-
set(flukso_getvalues_src flukso-getvalues.cpp)

add_executable(flukso_getvalues ${flukso-getvalues_src})

# Link the executable to the gridlicense library.
target_link_libraries(flukso_getvalues libflukso
	  ${PB_LIBRARY} ${Boost_LIBRARIES} ${SSL_CRYPTO})

# add programs to the install target - do not install the hashbench benchmark program.
INSTALL(PROGRAMS 
  ${CMAKE_CURRENT_BINARY_DIR}/flukso-getvalues
  DESTINATION bin)

