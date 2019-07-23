all: limit_ex

limit_ex: limit_ex.c
	@echo "[Building $@]"
	@gcc $? -o $@
	@echo "[Running $@]"
	@./$@

clean:
	@echo "[Deleting binaries]"
	@rm -f limit_ex
