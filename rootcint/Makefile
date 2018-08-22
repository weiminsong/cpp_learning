#---------------------------------------------------
LDFLAGS       = -I$(ROOTSYS)/include
LD            = CC

LIBS          = $(ROOTSYS)/lib/*.sl -lXpm -lX11 -lm -ldld

HDRS          = MyClass.h

SRCS          = main.C MyClass.C mydict.C

OBJS          = main.o MyClass.o mydict.o

PROGRAM       = myroot

all:            $(PROGRAM)

$(PROGRAM):     $(OBJS)
		@echo "Linking $(PROGRAM) ..."
		@$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o $(PROGRAM)
		@echo "done"

clean:;         @rm -f $(OBJS) core

###
MyClass.o: MyClass.h

mydict.C: MyClass.h
	@echo "Generating dictionary ..."
	@rootcint mydict.C -c MyClass.h
#---------------------------------------------------
