.PHONY: all clean

clean:
	-rm -f fill_mem fill_mem.o

CFLAGS=-std=c99 -g -O2 -Wall
all: fill_mem
fill_mem: fill_mem.o
	$(CC) $(LDFLAGS) $< -o $@
