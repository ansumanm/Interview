all: writer reader

writer: writer.c
	@echo "[Building Writer...]"
	@gcc $? -o $@

reader: reader.c
	@echo "[Building Reader...]"
	@gcc $? -o $@

clean:
	@echo "[Cleaning up binaries ...]"
	@rm -f writer;
	@rm -f reader;
