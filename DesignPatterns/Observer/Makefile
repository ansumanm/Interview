all: ex

ex: broadcaster.cpp
	@echo [Building $@]
	@g++ $? -o ex
	@echo [Done]
	@echo [Running $@]
	@./$@
	@echo [Done]

clean: 
	@echo [Deleting Binaries]
	@rm -f ex
