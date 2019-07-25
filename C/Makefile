all: align

%: %.c
	@gcc $? -o $@

defines: align.c
	gcc -dM -E $?

includes: align.c
	gcc -MD  align.c
