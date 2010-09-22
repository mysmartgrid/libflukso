include Makefile.inc

DIRS    = src 
OBJLIBS = libsubsub.a
LIBS    = -lsubsub

all : $(DIRS)

$(EXE) : main.o $(OBJLIBS)
	$(ECHO) $(LD) -o $(EXE) $(OBJS) $(LIBS)
	$(LD) -o $(EXE) $(OBJS) $(LIBS)

src : force_look
	$(ECHO) "looking into subdir : $."
	cd src; $(MAKE) $(MFLAGS)

clean:
	$(ECHO) "cleaning up in $(DIRS)"
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean ); done

force_look :
	true
