include ../Makefile.inc

CFLAGS+=-I$(LIBRARY_PATH)/include
#LDFLAGS=-static
LDFLAGS=-L$(LIBRARY_PATH)/lib -L. -ljson -lcurl -lpopt
SOURCES=flukso-getvalues.cpp
SOURCES+=flukso.cpp config.cpp exporter-text.cpp exporter-xml.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=flukso-getvalues

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
