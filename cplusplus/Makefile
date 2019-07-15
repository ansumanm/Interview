SRCDIR := src
OBJDIR := obj

VPATH = $(SRCDIR)

all: refEx objSl arrD smartPtr autoptr | obj
	@echo [Running Reference Example]
	@obj/refEx
	@echo [Running Object Slicing Example]
	@obj/objSl
	@echo [Running Array Example] 
	@obj/arrD
	@echo [Running Smart Pointer Example] 
	@obj/smartPtr
	@echo [Running Auto Pointer Example] 
	@obj/autoptr

obj:
	@echo [Creating obj]
	@mkdir obj

refEx: src/referenceEx.cpp | obj
	@echo [Building $@]
	@cd $(OBJDIR); g++ -std=c++11 ../$? -o $@

objSl: src/objectSlicingEx.cpp | obj
	@echo [Building $@]
	@cd $(OBJDIR); g++ ../$? -o $@

arrD: src/arrayDecay.cpp | obj
	@echo [Building $@]
	@cd $(OBJDIR); g++ ../$? -o $@

smartPtr: src/smartPtrEx.cpp | obj
	@echo [Building $@]
	@cd $(OBJDIR); g++ ../$? -o $@

autoptr: src/autoptrEx.cpp | obj
	@echo [Building $@]
	@cd $(OBJDIR); g++ ../$? -o $@

clean:
	rm -rf obj
