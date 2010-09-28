# -*- mode: cmake; -*-

set(hdrs 
  common.hpp
  config.hpp
  error.hpp
  exporter.hpp
  exporter-text.hpp
  exporter-xml.hpp
  flukso.hpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB all_flukso_src *.cpp *.hpp)
set(flukso_src ${all_flukso_src})
ADD_LIBRARY(flukso ${flukso_src})

install(FILES ${hdrs} DESTINATION include/flukso)
install(TARGETS flukso
        ARCHIVE DESTINATION lib)


