CC=g++
LIBRARY_PATH=/p/hpc/smartenergy/md/libraries
CFLAGS=-c -Wall -I. -I$(LIBRARY_PATH)/include -std=c++0x -pedantic -fPIC -O3
#LDFLAGS=-static
LDFLAGS=-L$(LIBRARY_PATH)/lib -ljson -lcurl -lpopt
SOURCES=flukso-checkhealth.cpp
#SOURCES+=allocation.cpp reportwriter.cpp schedulearchive.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=flukso-checkhealth

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# GCC autodepend-fu
.cpp.o:
	$(CC) $(CFLAGS) -MD $< -o $@
	@sed 's,\($*\.o\)[ :]*\(.*\),$@ : $$\(wildcard \2\)\n\1 : \2,g' $*.d > /dev/null
#@sed -i 's,\($*\.o\)[ :]*\(.*\),$@ : $$\(wildcard \2\)\n\1 : \2,g' $*.d
	
.PHONY: clean
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) *.d

-include $(SOURCES:.cpp=.d)
