# -*- mode: cmake; -*-

#set(hdrs 
#)

file(GLOB libflukso_src *.cpp *.hpp)
ADD_LIBRARY(libflukso ${libflukso_src})

install(FILES ${hdrs} DESTINATION include/libflukso)
install(TARGETS libflukso
        ARCHIVE DESTINATION lib)


