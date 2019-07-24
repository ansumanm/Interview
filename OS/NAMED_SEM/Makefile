all: p1 p_odd p_even sem_unlink

%: %.c
	gcc $? -o $@ -lpthread -lrt

clean:
	rm -f p1
	rm -f p_odd
	rm -f p_even
