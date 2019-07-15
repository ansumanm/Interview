SRCDIR := src
OBJDIR := obj

VPATH = $(SRCDIR)

all: refEx objSl | obj

obj:
	@echo [Creating obj]
	@mkdir obj

refEx: src/referenceEx.cpp | obj
	@echo [Building $@]
	@cd $(OBJDIR); g++ -std=c++11 ../$? -o $@

objSl: src/objectSlicingEx.cpp | obj
	@echo [Building $@]
	@cd $(OBJDIR); g++ ../$? -o $@

test: all
	@echo [Running Reference Example]
	@obj/refEx
	@echo [Running Object Slicing Example]
	@obj/objSl

clean:
	rm -rf obj
