all: ex1 ex2 ex3

ex1: ex1.cpp
	@echo "[Building $@ ...]"
	@g++ --std=c++1z ex1.cpp -o ex1
	@echo "[Running $@ ...]"
	@./ex1
	@echo "[Done ...]"

ex2: ex2.cpp
	@echo "[Building $@ ...]"
	@g++ --std=c++1z $? -o $@
	@echo "[Running $@ ...]"
	@./$@
	@echo "[Done ...]"

ex3: ex3.cpp
	@echo "[Building $@ ...]"
	@g++ --std=c++1z $? -o $@
	@echo "[Running $@ ...]"
	@./$@
	@echo "[Done ...]"

clean:
	@echo "[Deleting binaries ...]"
	@rm -f ./ex1
	@rm -f ./ex2
	@rm -f ./ex3
	@echo "[Done ...]"
	
