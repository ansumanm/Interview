SRCDIR := src
OBJDIR := obj
TARGETS: refEx objSl arrD smartPtr autoptr unique_ptr \
   	shared_ptr weak_ptr copycon explicitEx initializerList
TARGETS_LOC: $(addprefix $(OBJDIR)/,$TARGETS)
VPATH = $(SRCDIR)

all: $(TARGET_LOC) | $(OBJDIR)
obj:
	@echo [Creating obj]
	@mkdir obj

refEx: src/referenceEx.cpp | obj
	@echo [Building $@]
	@cd $(OBJDIR); g++ -std=c++11 ../$? -o $@
	@echo [Running Reference Example]
	@obj/refEx

objSl: src/objectSlicingEx.cpp | obj
	@echo [Building $@]
	@cd $(OBJDIR); g++ ../$? -o $@
	@echo [Running Object Slicing Example]
	@obj/objSl

arrD: src/arrayDecay.cpp | obj
	@echo [Building $@]
	@cd $(OBJDIR); g++ ../$? -o $@
	@echo [Running Array Example] 
	@obj/arrD

smartPtr: src/smartPtrEx.cpp | obj
	@echo [Building $@]
	@cd $(OBJDIR); g++ ../$? -o $@
	@echo [Running Smart Pointer Example] 
	@obj/smartPtr

autoptr: src/autoptrEx.cpp | obj
	@echo [Building $@]
	@cd $(OBJDIR); g++ ../$? -o $@
	@echo [Running Auto Pointer Example] 
	@obj/autoptr

unique_ptr: src/unique_ptrEx.cpp
	@echo [Building $@]
	@cd $(OBJDIR); g++ -std=c++11 ../$? -o $@
	@echo [Running Unique Pointer Example] 
	@obj/$@

shared_ptr: src/shared_ptrEx.cpp
	@echo [Building $@]
	@cd $(OBJDIR); g++ -std=c++11 ../$? -o $@
	@echo [Running Shared Pointer Example] 
	@obj/$@

weak_ptr: src/weak_ptrEx.cpp
	@echo [Building $@]
	@cd $(OBJDIR); g++ -std=c++11 ../$? -o $@
	@echo [Running Weak Pointer Example] 
	@obj/$@

copycon: src/copyConstructorEx.cpp
	@echo [Building $@]
	@cd $(OBJDIR); g++ -std=c++11 ../$? -o $@
	@echo [Running Copy Constructr Example] 
	@obj/$@

explicitEx: src/explicitEx.cpp
	@echo [Building $@]
	@cd $(OBJDIR); g++ -std=c++11 ../$? -o $@
	@echo [Running Explicit Keyword Example] 
	@obj/$@

initializerList: src/initializerEx.cpp
	@echo [Building $@]
	@cd $(OBJDIR); g++ -std=c++11 ../$? -o $@
	@echo [Running $@ Example] 
	@obj/$@

clean:
	rm -rf obj
